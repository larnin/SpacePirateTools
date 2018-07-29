#ifndef OBJECTVALUEASSET_H
#define OBJECTVALUEASSET_H

#include "objectvaluebase.h"
#include <QString>
#include <ProjectInfos/assettype.h>

class ObjectValueAsset : public ObjectValueBase
{
public:
    ObjectValueAsset(AssetType type);
    ObjectValueAsset(const QJsonObject & obj);
    ObjectValueAsset(const ObjectValueAsset &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueAsset>(*this); }

    inline AssetType getAssetType() const { return m_type; }

    QString toString() const override;
    QWidget* createUi() override;

    QString assetName;

protected:
    void onSave(QJsonObject & obj) const override;

private:
    ValueType assetToValueType(AssetType type);
    AssetType valueToAssetType(ValueType type);

    AssetType m_type;
};

#endif // OBJECTVALUEASSET_H
