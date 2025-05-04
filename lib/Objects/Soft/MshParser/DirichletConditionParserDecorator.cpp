#include <Objects/Soft/MshParser/DirichletConditionParserDecorator.h>

namespace Barta::Objects::Soft::MshParser {
DirichletConditionParserDecorator::DirichletConditionParserDecorator(
    MshDataParserInterface& decorated
) noexcept:
    decorated(decorated) {}

Mesh DirichletConditionParserDecorator::parse(
    const MshData& mshData
) const {
    auto mesh = this->decorated.parse(mshData);

    unsigned int dirichletConditionGroupTag = 0;
    for (const auto& physicalGroup: mshData.physicalGroups) {
        if (physicalGroup.name != "\"DirichletCondition\"") {
            continue;
        }

        dirichletConditionGroupTag = physicalGroup.tag;

        break;
    }

    if (dirichletConditionGroupTag == 0) {
        return mesh;
    }

    std::vector<unsigned int> entityTagsInDirichletGroup;
    for (const auto& entity: mshData.entities.at(MshData::EntityDimension::SURFACE)) {
        for (const auto& entityPhysicalGroupTag: entity.physicalGroupTags) {
            if (entityPhysicalGroupTag != dirichletConditionGroupTag) {
                continue;
            }

            entityTagsInDirichletGroup.push_back(entity.tag);
        }
    }

    std::vector<unsigned int> dirichletNodeTags;
    for (const auto& element: mshData.triangleElements) {
        if (std::ranges::find(entityTagsInDirichletGroup, element.entityTag) != entityTagsInDirichletGroup.end()) {
            for (const auto& elementNodeTag: element.nodeTags) {
                dirichletNodeTags.push_back(elementNodeTag);
            }
        }
    }

    std::ranges::sort(dirichletNodeTags);
    const auto toErase = std::ranges::unique(dirichletNodeTags);
    dirichletNodeTags.erase(toErase.begin(), toErase.end());
    unsigned int dirichletNodeCount = 0;
    std::vector<Node> freeNodes;
    std::vector<Node> dirichletNodes;
    for (auto& node: mesh.nodes) {
        if (std::ranges::binary_search(dirichletNodeTags, node.tag) && !node.isZeroDirichlet) {
            node.isZeroDirichlet = true;

            ++dirichletNodeCount;
        }

        if (node.isZeroDirichlet) {
            dirichletNodes.push_back(node);
        } else {
            freeNodes.push_back(node);
        }
    }

    mesh.dirichletNodeCount += dirichletNodeCount;
    std::ranges::move(dirichletNodes, std::back_inserter(freeNodes));
    mesh.nodes = freeNodes;

    return mesh;
}
}
