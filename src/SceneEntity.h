#pragma once

#include <cstdint>
#include <string>
#include "UI/IDrawable.h"
#include "Rendering/ModelInstance.h"

namespace omp
{
    class Scene;
    class SceneEntity : public IDrawable
    {
    private:
        int32_t m_Id;
    protected:
        std::string m_Name;
        // TODO: rename to instance, and divide with material
        std::shared_ptr<omp::ModelInstance> m_ModelInstance;

    public:
        SceneEntity();
        SceneEntity(const std::string& inName, const std::shared_ptr<omp::ModelInstance>& inModel);
        virtual ~SceneEntity() = default;
        int32_t getId() const { return m_Id; }

        std::string getName() const { return m_Name; }
        void setName(const std::string& inName) { m_Name = inName; }

        std::shared_ptr<omp::ModelInstance> getModelInstance() const { return m_ModelInstance; }
        void setModelInstance(const std::shared_ptr<omp::ModelInstance>& instance) { m_ModelInstance = instance; }

        void setTranslation(const glm::vec3& trans);
        void setRotation(const glm::vec3& rot);
        void setScale(const glm::vec3& scale);

        virtual void draw() override;

        virtual void onSceneSave(JsonParser<>& parser, omp::Scene* scene);
        virtual void onSceneLoad(JsonParser<>& parser, omp::Scene* scene);
        virtual std::string getClassName() const { return "SceneEntity"; }
    };
}
