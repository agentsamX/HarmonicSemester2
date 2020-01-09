
#include "ControlTab.h"
Selectable ControlTab::m_selectable = Selectable("Controls");

void ControlTab::CreateTab()
{
	bool temp = false;

	if (ImGui::BeginTabItem(m_selectable.GetName().c_str(), m_selectable.GetSelected()))
	{
		temp = true;

		ImGui::EndTabItem();
	}

	if (temp)
		CreateEditor();
}

void ControlTab::CreateEditor()
{

	if (m_selectable.GetSelected())
	{
		if (ImGui::TreeNode("Animation Controls"))
		{
			if (ImGui::Button("Hadouken Animation", ImVec2(150.f, 20.f)))
			{
				auto& animController = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
				animController.SetActiveAnim(1);
			}
			if (ImGui::Button("Idle Animation", ImVec2(150.f, 20.f)))
			{
				auto& animController = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
				animController.SetActiveAnim(0);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Position Controls"))
		{
			auto& transKen = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
			float posX = transKen.GetPosition().x;
			float posY = transKen.GetPosition().y;
			float posZ = transKen.GetPosition().z;
			if (ImGui::DragFloat("PosX", &posX , 0.01f, -400.f, 400.f))
			{
				transKen.SetPosition(vec3(posX, posY, posZ));
			}
			if (ImGui::DragFloat("PosY", &posY, 0.01f, -400.f, 400.f))
			{
				transKen.SetPosition(vec3(posX, posY, posZ));
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Camera Rotation"))
		{
			auto& cameraRot = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
			float angle = cameraRot.GetRotationAngleZ()*(180/PI);
			if (ImGui::SliderFloat("Camera Rotation", &angle, -360.f,360.f,"%.3f",1.0F))
			{
				cameraRot.SetRotationAngleZ(angle/(180/PI));
			}
			ImGui::TreePop();
		}
	}
}
