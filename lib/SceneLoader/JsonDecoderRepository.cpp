#include <SceneLoader/JsonDecoderRepository.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/CircleHitbox.h>
#include <Hitbox/OBB_Hitbox.h>
#include <SceneLoader/JsonDecodeException.h>

namespace Barta::SceneLoader {

std::unique_ptr<HitboxInterface> JsonDecoderRepository::decodeHitbox(
    const json& json
) const {
    const auto& hitboxJson = json.at("hitbox");
    if (!hitboxJson.is_object()) {
        throw JsonDecodeException("Hitbox should be an object");
    }

    const auto& jsonType = hitboxJson.at("type");
    if (!jsonType.is_string()) {
        throw JsonDecodeException("Hitbox type should be a string");
    }

    const auto& type = jsonType.get<std::string>();
    if (type == "CIRCLE") {
        return std::make_unique<CircleHitbox>(hitboxJson.get<Circle>());
    }

    if (type == "OBB") {
        return std::make_unique<OBB_Hitbox>(hitboxJson.get<OBB>());
    }

    throw JsonDecodeException("Unknown type = " + type + " for hitbox decode");
    // if (type == "TRIANGLE") {
    //     return std::make_unique<Trian>(hitboxJson.get<Triangle>());
    // }
}

GraphicsData JsonDecoderRepository::decodeGraphicsData(
    const json& json
) const {
    auto merger = SpriteMerger();
    const auto& jsonSprites = json.at("sprites");
    if (!jsonSprites.is_array()) {
        throw JsonDecodeException("Sprites should be an array");
    }

    // if (jsonSprites.empty()) { // Mesh objects have no sprites for now
    //     throw JsonDecodeException("There should be at least one sprite");
    // }

    for (const auto& jsonSprite: jsonSprites) {
        const auto& jsonType = jsonSprite.at("type");
        if (!jsonType.is_string()) {
            throw JsonDecodeException("Sprite type should be a string");
        }

        auto spriteBuilder = jsonSprite.get<SpriteBuilder>();
        auto type = jsonType.get<std::string>();
        if (type == "CIRCLE") {
            merger.addCircleSprite(spriteBuilder.buildCircleSprite());

            continue;
        }

        if (type == "RECTANGLE") {
            merger.addRectangleWithColors(spriteBuilder.buildRectangleSprite());

            continue;
        }

        if (type == "RECTANGLE_WITH_COLORS") {
            merger.addRectangleWithColors(spriteBuilder.buildRectangleWithColorsSprite());

            continue;
        }

        if (type == "STRING") {
            merger.addString(spriteBuilder.buildStringSprite());

            continue;
        }

        if (type == "TRIANGLE") {
            merger.addTriangle(spriteBuilder.buildTriangleSprite());

            continue;
        }

        if (type == "TRIANGLE_WITH_COLORS") {
            merger.addTriangle(spriteBuilder.buildTriangleWithColorsSprite());

            continue;
        }

        throw JsonDecodeException("Unknown type = " + type + " for sprite decode");
    }

    int z_index = 0;
    if (json.contains("z_index")) {
        z_index = json.at("z_index").get<int>();
    }

    Transformation transformation = Transformation::Identity();
    if (json.contains("transformation")) {
        transformation = json.at("transformation").get<Transformation>();
    }

    return {transformation, merger.merge(false), z_index};
}

Events::Events::CameraTransformationEvent JsonDecoderRepository::decodeCamera(
    const json& json
) {
    Events::Events::CameraTransformationEvent event;
    const auto& eye = json.at("eye");
    if (!eye.is_object()) {
        throw JsonDecodeException("Camera has no eye position");
    }

    const auto& center = json.at("center");
    if (!center.is_object()) {
        throw JsonDecodeException("Camera has no center position");
    }

    const auto& up = json.at("up");
    if (!up.is_object()) {
        throw JsonDecodeException("Camera has no up vector");
    }

    event.eye = eye;
    event.center = center;
    event.up = up;

    return event;
}
}
