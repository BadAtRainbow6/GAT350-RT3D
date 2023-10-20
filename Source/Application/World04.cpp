#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#define INTERLEAVE

namespace nc
{
    bool World04::Initialize()
    {
        m_material = GET_RESOURCE(Material, "materials/grid.mtrl");
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(m_material);
        m_model->Load("models/buddha.obj", glm::vec3{ 0 }, glm::vec3{ 90, 0, 0 });
        return true;
    }

    void World04::Shutdown()
    {
    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0], 0.1f);
        ImGui::End();

        ImGui::Begin("Light");
        ImGui::ColorEdit3("Ambient", glm::value_ptr(lightAmbient));
        ImGui::ColorEdit3("Diffuse", glm::value_ptr(lightDiffuse), 0.2f);
        ImGui::DragFloat3("Position", glm::value_ptr(lightPosition), 0.2f);
        ImGui::End();

        //m_transform.rotation.z += 90 * dt;

        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * -dt : 0;

        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * dt : 0;

        m_time += dt;

        auto material = m_model->GetMaterial();
        material->ProcessGui();
        material->Bind();

        //model matrix
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        material->GetProgram()->SetUniform("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
        material->GetProgram()->SetUniform("projection", projection);

        material->GetProgram()->SetUniform("light.position", lightPosition);
        material->GetProgram()->SetUniform("light.color", lightDiffuse);
        material->GetProgram()->SetUniform("ambientLight", lightAmbient);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();


        // render

        //will only draw a wire mesh
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //will draw the full model
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_model->Draw(GL_TRIANGLES);

        ENGINE.GetSystem<Gui>()->Draw();


        // post-render
        renderer.EndFrame();
    }
}
