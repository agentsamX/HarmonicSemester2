#include "HorizontalScroll.h"

HorizontalScroll::HorizontalScroll()
{
}

void HorizontalScroll::Update()
{//error is in the if statement logic
	if (m_focus->GetPosition().x > m_cam->m_localPosition.x + m_offset)
	{
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);

		m_cam->SetPosition(vec3(m_cam->GetPosition().x + difference, m_cam->GetPosition().y, m_cam->GetPosition().z));

	}
	if (m_focus->GetPosition().x < m_cam->m_localPosition.x - m_offset)
	{
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);

		m_cam->SetPosition(vec3(m_cam->GetPosition().x + difference, m_cam->GetPosition().y, m_cam->GetPosition().z));
	}
}

Camera * HorizontalScroll::GetCam() const
{
	return m_cam;
}

Transform * HorizontalScroll::GetFocus() const
{
	return m_focus;
}

float HorizontalScroll::GetOffset() const
{
	return m_offset;
}

void HorizontalScroll::SetCam(Camera * cam)
{
	m_cam = cam;
}

void HorizontalScroll::SetFocus(Transform * focus)
{
	m_focus = focus;
}

void HorizontalScroll::SetOffset(float offset)
{
	m_offset = offset;
}



