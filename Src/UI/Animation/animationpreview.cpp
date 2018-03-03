#include "animationpreview.h"
#include "animationsinfos.h"
#include "ProjectInfos/projectinfos.h"
#include "ProjectInfos/configs.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <algorithm>

AnimationPreview::AnimationPreview(AnimationsInfos *infos, QWidget *parent)
    : QSFMLCanvas(60, parent)
    , m_animationInfos(infos)
    , m_textureEnabled(false)
    , m_currentFrame(0)
    , m_frameTime(0)
    , m_animationPaused(false)
{
    updateTexture(infos->getAnimationData().imageName);
}

void AnimationPreview::updateTexture(const QString & name)
{
    m_textureEnabled = false;
    if(name.isEmpty())
        return;

    AssetType img = AssetType::Image;
    QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(img) + "/" + name/* + "." + assetTypeExtension(img)*/;

    m_textureEnabled = m_texture.loadFromFile(fullName.toStdString());
}

void AnimationPreview::OnUpdate()
{
    RenderWindow::clear(Configs::instance().animationBackgroundColor);

    if(!m_textureEnabled || m_animationInfos->getAnimationData().empty())
        return;

    auto rect = globalRect(5);
    auto size = RenderWindow::getSize();

    if(float(rect.width) / rect.height > float(size.x) / size.y)
    {
        int newHeight = float(size.y) / size.x * rect.width;
        rect.top -= (newHeight - rect.height) / 2;
        rect.height = newHeight;
    }
    else
    {
        int newWidth = float(size.x) / size.y * rect.height;
        rect.left -= (newWidth - rect.width) / 2;
        rect.width = newWidth;
    }

    RenderWindow::setView(sf::View(sf::FloatRect(rect)));

    updateAnimationTime();

    const Frame & f(m_animationInfos->getAnimationData()[m_currentFrame]);

    sf::Sprite s(m_texture, f.rect);
    s.setOrigin(sf::Vector2f(f.offset));
    s.setPosition(sf::Vector2f(0, 0));

    RenderWindow::draw(s);
}

void AnimationPreview::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
        m_animationPaused = ! m_animationPaused;
}

void AnimationPreview::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() == 0)
        return;

    m_animationPaused = true;

    if(event->angleDelta().y() > 0)
        m_currentFrame = m_currentFrame >= m_animationInfos->getAnimationData().size() - 1 ? 0 : m_currentFrame + 1;
    if(event->angleDelta().y() < 0)
        m_currentFrame = m_currentFrame == 0 ? m_animationInfos->getAnimationData().size() - 1 : m_currentFrame - 1;
}

void AnimationPreview::updateAnimationTime()
{
    float time = m_clock.restart().asSeconds();

    if(m_animationPaused)
        return;

    m_frameTime += time;

    if(m_animationInfos->getAnimationData().empty())
        return;

    if(m_currentFrame > m_animationInfos->getAnimationData().size())
        m_currentFrame = m_animationInfos->getAnimationData().size() - 1;

    if(m_frameTime >= m_animationInfos->getAnimationData()[m_currentFrame].time)
    {
        m_frameTime -= m_animationInfos->getAnimationData()[m_currentFrame].time;
        m_currentFrame++;
    }
    if(m_currentFrame >= m_animationInfos->getAnimationData().size())
        m_currentFrame = 0;
}

sf::IntRect AnimationPreview::globalRect(int border)
{
    sf::Vector2i minPos(0, 0);
    sf::Vector2i maxPos(0, 0);

    for(const Frame & f : m_animationInfos->getAnimationData())
    {
        sf::Vector2i fMin(-f.offset);
        sf::Vector2i fMax(fMin + sf::Vector2i(f.rect.width, f.rect.height));

        minPos.x = std::min(fMin.x, minPos.x);
        minPos.y = std::min(fMin.y, minPos.y);
        maxPos.x = std::max(fMax.x, maxPos.x);
        maxPos.y = std::max(fMax.y, maxPos.y);
    }

    minPos -= sf::Vector2i(border, border);
    maxPos += sf::Vector2i(border, border);

    if(maxPos.x <= minPos.x)
        maxPos.x = minPos.x + 1;
    if(maxPos.y <= minPos.y)
        maxPos.y = maxPos.y + 1;

    return sf::IntRect(minPos, maxPos - minPos);
}
