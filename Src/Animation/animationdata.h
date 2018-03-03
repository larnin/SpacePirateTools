#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

#include <QString>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

struct Frame
{
    sf::IntRect rect;
    sf::Vector2i offset;
    float time;
};

class AnimationData : private std::vector<Frame>
{
public:
    AnimationData() = default;
    AnimationData(const QString & fileName);
    using std::vector<Frame>::push_back;
    using std::vector<Frame>::pop_back;
    using std::vector<Frame>::begin;
    using std::vector<Frame>::end;
    using std::vector<Frame>::front;
    using std::vector<Frame>::back;
    using std::vector<Frame>::insert;
    using std::vector<Frame>::erase;
    using std::vector<Frame>::emplace_back;
    using std::vector<Frame>::clear;
    using std::vector<Frame>::operator [];
    using std::vector<Frame>::size;
    using std::vector<Frame>::empty;

    void save(const QString & fileName) const;

    QString imageName;

private:
    void load(const QString & fileName);
};

#endif // ANIMATIONDATA_H
