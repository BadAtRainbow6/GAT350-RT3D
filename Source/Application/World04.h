#pragma once
#include "Framework/World.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Transform.h"
#include "Renderer/Renderer.h"

namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	public:
		glm::vec3 lightPosition{ 1 };
		glm::vec3 lightDiffuse{ 1 };
		glm::vec3 lightAmbient{ 0.5f };
	private:
		float m_time;
		float m_speed = 5;

		Transform m_transform;

		res_t<Model> m_model;
		res_t<Program> m_program;
		res_t<Texture> m_texture;
		res_t<Material> m_material;
		res_t<VertexBuffer> m_vertexBuffer;
	};
}