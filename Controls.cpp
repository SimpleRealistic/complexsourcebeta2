/*
Syn's AyyWare Framework 2015
*/

#include "Controls.h"
#include "RenderManager.h"
//#include "Utilities/CRC32.h"
#include "CRC32.h"
#include "Menu.h"

#pragma region Base Control
void CControl::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CControl::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CControl::GetSize(int &w, int &h)
{
	w = m_iWidth;
	h = m_iHeight;
}

bool CControl::Flag(int f)
{
	if (m_Flags & f)
		return true;
	else
		return false;
}

POINT CControl::GetAbsolutePos()
{
	POINT p;
	RECT client = parent->GetClientArea();
	if (parent)
	{
		p.x = m_x + client.left;
		p.y = m_y + client.top + 29;
	}

	return p;
}

void CControl::SetFileId(std::string fid)
{
	FileIdentifier = fid;
}
#pragma endregion Implementations of the Base control functions

#pragma region CheckBox
CCheckBox::CCheckBox()
{
	Checked = false;

	m_Flags = UIFlags::UI_Clickable | UIFlags::UI_Drawable | UIFlags::UI_SaveFile;
	m_iWidth = 13;
	m_iHeight = 13;

	FileControlType = UIControlTypes::UIC_CheckBox;
}

void CCheckBox::SetState(bool s)
{
	Checked = s;
}

bool CCheckBox::GetState()
{
	return Checked;
}

void CCheckBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Outline(a.x, a.y, 13, 13, Color(255, 255, 255, 255)); //wei�e au�enlinie von der checkbox
	int CheckBoxR = 155;
	int CheckBoxG = 255;
	int CheckBoxB = 50;

	if (hover)
	{
		if (Checked)
		{
			Render::Clear(a.x + 2, a.y + 2, 9, 9, Color(CheckBoxR, CheckBoxG, CheckBoxB, 255));
		}
		else
		{
			Render::Clear(a.x + 2, a.y + 2, 9, 9, Color(129, 129, 129, 255)); //leicht grau
		}
		Render::Outline(a.x + 2, a.y + 2, 9, 9, Color(20, 20, 20, 80)); //schwarz
	}
	else if (Checked)
	{
		Render::Clear(a.x + 2, a.y + 2, 9, 9, Color(CheckBoxR, CheckBoxG, CheckBoxB, 255));
		Render::Outline(a.x + 2, a.y + 2, 9, 9, Color(20, 20, 20, 80)); //schwarz
	}
}

void CCheckBox::OnUpdate() { m_iWidth = 13; 	m_iHeight = 13; }

void CCheckBox::OnClick()
{
	Checked = !Checked;
}
#pragma endregion Implementations of the Check Box functions

#pragma region CheckBox2
CCheckBox2::CCheckBox2()
{
	Checked = false;

	m_Flags = UIFlags::UI_Clickable | UIFlags::UI_Drawable | UIFlags::UI_SaveFile;
	m_iWidth = 10;
	m_iHeight = 10;

	FileControlType = UIControlTypes::UIC_CheckBox;
}

void CCheckBox2::SetState(bool s)
{
	Checked = s;
}

bool CCheckBox2::GetState()
{
	return Checked;
}

void CCheckBox2::Draw(bool hover)
{
	int CheckBoxR = 155;
	int CheckBoxG = 255;
	int CheckBoxB = 50;
	POINT a = GetAbsolutePos();
	Render::GradientV(a.x, a.y, 10, 10, Color(55, 55, 55, 255), Color(40, 40, 40, 245));
	Render::Outline(a.x, a.y, 10, 10, Color(2, 2, 2, 255));

	int red;
	int green;
	int blue;

	if (Checked)
	{
		Render::Clear(a.x + 2, a.y + 2, 9, 9, Color(CheckBoxR, CheckBoxG, CheckBoxB, 255));
	}
}

void CCheckBox2::OnUpdate() { m_iWidth = 10; m_iHeight = 10; }

void CCheckBox2::OnClick()
{
	Checked = !Checked;
}
#pragma endregion Implementations of the Check Box 2 functions

#pragma region Label
CLabel::CLabel()
{
	m_Flags = UIFlags::UI_Drawable;
	Text = "Default";
	FileIdentifier = "Default";
}

void CLabel::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Text(a.x, a.y, Color(245, 245, 245, 255), Render::Fonts::MenuBold, Text.c_str()); //TEXt farbe (wei�)
}

void CLabel::SetText(std::string text)
{
	Text = text;
}

void CLabel::OnUpdate() {}
void CLabel::OnClick() {}
#pragma endregion Implementations of the Label functions

#pragma region GroupBox
CGroupBox::CGroupBox()
{
	Items = 1;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, Text.c_str());
	Render::Clear(a.x, a.y, m_iWidth, m_iHeight, Color(37, 137, 255));// menu mini box color (37, 137, 255, 255)
	int GroupBoxR = 30;
	int GroupBoxG = 30;
	int GroupBoxB = 30;
	Vertex_t Verts2[4];
	Verts2[0].Init(Vector2D(a.x + 1, a.y + 1));
	Verts2[1].Init(Vector2D(a.x + m_iWidth - 1, a.y));
	Verts2[2].Init(Vector2D(a.x + m_iWidth - 1, a.y + 13));
	Verts2[3].Init(Vector2D(a.x, a.y + 13));

	Render::PolygonOutline(4, Verts2, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255), Color(GroupBoxR - 30, GroupBoxG - 30, GroupBoxB - 30, 0)); //

	int TextX = a.x + (m_iWidth / 2) - (txtSize.left / 2);
	Render::Text(TextX, a.y - (txtSize.bottom / 2) + 6, Color(255, 255, 255, 255), Render::Fonts::MenuBold, Text.c_str());

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(48, 48, 48, 0));
	Render::Outline(a.x + 1, a.y + 1, m_iWidth - 2, m_iHeight - 2, Color(0, 0, 0, 0));

	/*Render::Line(a.x, a.y, a.x + 12, a.y, Color(129, 129, 129, 255));
	Render::Line(a.x + 15 + txtSize.right + 5, a.y, a.x + m_iWidth, a.y, Color(129, 129, 129, 255));
	Render::Line(a.x, a.y, a.x, a.y + m_iHeight, Color(129, 129, 129, 255));
	Render::Line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, Color(129, 129, 129, 255));
	Render::Line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight, Color(129, 129, 129, 255));*/
}

void CGroupBox::SetText(std::string text)
{
	Text = text;
}

void CGroupBox::PlaceLabledControl(std::string Label, CTab *Tab, CControl* control)
{
	int x = m_x + 17;
	int y = m_y + Items * 25;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);

	x += m_iWidth / 2;

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((m_iWidth / 2) - 32, ch);
	Tab->RegisterControl(control);
	Items++;
}

void CGroupBox::PlaceLabledControl1(std::string Label, CTab *Tab, CControl* control, int c, int r)
{
	int CellW = (m_iWidth / Columns);
	int x = m_x + 10 + (c * CellW);
	int y = m_y + 26 + r * 22;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);

	x += CellW / 2;

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((CellW / 2) - 20, ch);
	Tab->RegisterControl(control);

	/*if (r > MaxRow)
	MaxRow = r;*/

	char szCRCBuffer[256];
	sprintf_s(szCRCBuffer, "%s%s", Text.c_str(), Label.c_str());
	control->SetFileID(CRC32(szCRCBuffer, strlen(szCRCBuffer)));

	m_iHeight = (MaxRow + 1) * 22 + 26;
}
///////////
void CGroupBox::OnUpdate() {}
void CGroupBox::OnClick() {}

CGroupBox2::CGroupBox2()
{
	Items = 1;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox2::Draw(bool hover)
{
	int GroupBoxR = 30;
	int GroupBoxG = 30;
	int GroupBoxB = 30;
	POINT a = GetAbsolutePos();
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, Text.c_str());
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(245, 245, 245, 0));
	Render::Text(a.x + 15, a.y - (txtSize.bottom / 2), Color(255, 255, 255, 255), Render::Fonts::MenuBold, Text.c_str());

	Render::Line(a.x, a.y, a.x + 12, a.y, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x + 15 + txtSize.right + 5, a.y, a.x + m_iWidth, a.y, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x, a.y, a.x, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
}

void CGroupBox2::SetText(std::string text)
{
	Text = text;
}

void CGroupBox2::PlaceLabledControl(std::string Label, CTab *Tab, CControl* control)
{
	int x = m_x + 16;
	int y = m_y + Items * 24;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);

	x += m_iWidth / 2;

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((m_iWidth / 2) - 32, ch);
	Tab->RegisterControl(control);
	Items++;
}

void CGroupBox2::OnUpdate() {}
void CGroupBox2::OnClick() {}

CGroupBox3::CGroupBox3()
{
	Items = 1;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox3::Draw(bool hover)
{
	int GroupBoxR = 30;
	int GroupBoxG = 30;
	int GroupBoxB = 30;
	POINT a = GetAbsolutePos();
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, Text.c_str());
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(245, 245, 245, 0));
	Render::Text(a.x + 15, a.y - (txtSize.bottom / 2), Color(255, 255, 255, 255), Render::Fonts::MenuBold, Text.c_str());

	Render::Line(a.x, a.y, a.x + 12, a.y, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x + 15 + txtSize.right + 5, a.y, a.x + m_iWidth, a.y, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x, a.y, a.x, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
	Render::Line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight, Color(GroupBoxR, GroupBoxG, GroupBoxB, 255));
}

void CGroupBox3::SetText(std::string text)
{
	Text = text;
}

void CGroupBox3::PlaceLabledControl(std::string Label, CTab *Tab, CControl* control)
{
	int x = m_x + 16;
	int y = m_y + Items * 17;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);

	x += m_iWidth / 2;

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((m_iWidth / 2) - 32, ch);
	Tab->RegisterControl(control);
	Items++;
}

void CGroupBox3::OnUpdate() {}
void CGroupBox3::OnClick() {}
#pragma endregion Implementations of the Group Box functions

#pragma region Sliders
CSlider::CSlider()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Clear(a.x, a.y + 5, m_iWidth, 2, Color(161, 161, 161, 255)); //slider farbe
	int SliderR = 155;
	int SliderG = 255;
	int SliderB = 50;

	float Ratio = Value / (Max - Min);
	float Location = Ratio*m_iWidth;

	Render::GradientV(a.x, a.y + 5, m_iWidth, 9, Color(54, 54, 54, 255), Color(66, 66, 66, 255));
	Render::GradientV(a.x, a.y + 5, Location, 9, Color(SliderR, SliderG, SliderB, 255), Color(SliderR + 30, SliderG + 30, SliderB + 30, 255)); //Fixen
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, 255));

	/*Render::Clear(a.x + Location, a.y + 1, 4, 9, Color(255, 0, 0, 255));
	Render::Outline(a.x + Location, a.y + 1, 4, 9, Color(20, 20, 20, 80));*/

	char buffer[24];
	sprintf_s(buffer, "%.2f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + (m_iWidth / 2) - txtSize.right / 2, a.y + 10, Color(255, 255, 255, 255), Render::Fonts::MenuBold, buffer); //Value Farbe (wei�)
}

void CSlider::OnUpdate() {
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider::GetValue()
{
	return Value;
}

void CSlider::SetValue(float v)
{
	Value = v;
}

void CSlider::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}

/////////////

CSlider2::CSlider2()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider2::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	float Ratio = Value / (Max - Min);
	float Location = Ratio*m_iWidth;


	//Render::Outline(a.x + 1, a.y + 6, m_iWidth - 2, 9, Color(48, 48, 48, 255));
	Render::GradientV(a.x, a.y + 5, m_iWidth, 9, Color(54, 54, 54, 255), Color(66, 66, 66, 255));
	Render::GradientV(a.x, a.y + 5, Location, 9, Color(155, 255, 50, 255), Color(155, 255, 50, 255));
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, 255));

	char buffer[24];
	sprintf_s(buffer, "%.2f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 10, Color(200, 200, 200, 255), Render::Fonts::MenuBold, buffer);
}

void CSlider2::OnUpdate() {
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider2::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider2::GetValue()
{
	return Value;
}

void CSlider2::SetValue(float v)
{
	Value = v;
}

void CSlider2::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}

////////////////////////////

CSlider3::CSlider3()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider3::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	float Ratio = Value / (Max - Min);
	float Location = Ratio*m_iWidth;

	int SliderR = 155;
	int SliderG = 255;
	int SliderB = 50;

	//Render::Outline(a.x + 1, a.y + 6, m_iWidth - 2, 9, Color(48, 48, 48, 255));
	Render::GradientV(a.x, a.y + 5, m_iWidth, 9, Color(54, 54, 54, 255), Color(66, 66, 66, 255));
	Render::GradientV(a.x, a.y + 5, Location, 9, Color(SliderR, SliderG, SliderB, 255), Color(SliderR + 30, SliderG + 30, SliderB + 30, 255));
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, 255));

	char buffer[24];
	sprintf_s(buffer, "%.1f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 10, Color(200, 200, 200, 255), Render::Fonts::MenuBold, buffer);
}

void CSlider3::OnUpdate() {
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider3::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider3::GetValue()
{
	return Value;
}

void CSlider3::SetValue(float v)
{
	Value = v;
}

void CSlider3::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}
#pragma endregion Implementations of the Slider functions

#pragma region KeyBinders

char* KeyStrings[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CKeyBind::CKeyBind()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

void CKeyBind::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(129, 129, 129, 255));
	if (hover)
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(30, 30, 30, 255), Color(60, 60, 60, 255));	//Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(255, 255, 255, 80));
	bool GoodKeyName = false;
	char NameBuffer[128];
	char* KeyName = "No Key";

	if (IsGettingKey)
	{
		KeyName = "<Press A Key>";
	}
	else
	{
		if (Key >= 0)
		{
			KeyName = KeyStrings[Key];
			if (KeyName)
			{
				GoodKeyName = true;
			}
			else
			{
				if (GetKeyNameText(Key << 16, NameBuffer, 127))
				{
					KeyName = NameBuffer;
					GoodKeyName = true;
				}
			}
		}

		if (!GoodKeyName)
		{
			KeyName = "No Key";
		}
	}


	Render::Text(a.x + 2, a.y + 2, Color(255, 255, 255, 255), Render::Fonts::MenuBold, KeyName);
}

void CKeyBind::OnUpdate() {
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	if (IsGettingKey)
	{
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE)
				{
					IsGettingKey = false;
					Key = -1;
					return;
				}

				Key = i;
				IsGettingKey = false;
				return;
			}
		}
	}
}

void CKeyBind::OnClick() {
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

int CKeyBind::GetKey()
{
	return Key;
}

void CKeyBind::SetKey(int key)
{
	Key = key;
}

#pragma endregion Implementations of the KeyBind Control functions

#pragma region Button
CButton::CButton()
{
	m_iWidth = 177;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	Text = "Default";
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButton::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(129, 129, 129, 255));
	if (hover)
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(53, 53, 53, 255), Color(53, 53, 53, 255));
	else
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(53, 53, 53, 255), Color(53, 53, 53, 255));

	RECT TextSize = Render::GetTextSize(Render::Fonts::MenuBold, Text.c_str());
	int TextX = a.x + (m_iWidth / 2) - (TextSize.left / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	Render::Text(TextX, TextY, Color(255, 255, 255, 255), Render::Fonts::MenuBold, Text.c_str()); //test farbe
}

void CButton::SetText(std::string text)
{
	Text = text;
}

void CButton::SetCallback(CButton::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButton::OnUpdate()
{
	m_iHeight = 26;
}

void CButton::OnClick()
{
	if (CallBack)
		CallBack();
}
#pragma endregion Implementations of the Button functions

#pragma region ComboBox
CComboBox::CComboBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_ComboBox;
}

void CComboBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 16 };
	Render::GradientV(a.x, a.y, m_iWidth, 16, Color(30, 30, 30, 200), Color(40, 40, 40, 255));
	Render::Outline(a.x, a.y, m_iWidth, 16, Color(20, 20, 20, 80));

	// Hover for the Top Box
	if (GUI.IsMouseInRegion(Region))
		Render::Outline(a.x, a.y, m_iWidth, 16, Color(70, 70, 70, 80));

	// If we have some items
	if (Items.size() > 0)
	{
		// The current item
		Render::Text(a.x + 2, a.y + 2, Color(100, 100, 100, 255), Render::Fonts::MenuBold, GetItem().c_str());

		// If the drop down part is open
		if (IsOpen)
		{
			Render::GradientV(a.x, a.y + 17, m_iWidth, Items.size() * 16, Color(30, 30, 30, 255), Color(40, 40, 40, 255));
			Render::Outline(a.x, a.y + 17, m_iWidth, Items.size() * 16, Color(70, 70, 70, 80));

			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 17 + i * 16, m_iWidth, 16 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					Render::GradientV(a.x, a.y + 17 + i * 16, m_iWidth, 16, Color(30, 30, 30, 200), Color(40, 40, 40, 255));
				}

				Render::Text(a.x + 2, a.y + 19 + i * 16, Color(100, 100, 100, 255), Render::Fonts::MenuBold, Items[i].c_str());
			}
		}
	}
}

void CComboBox::AddItem(std::string text)
{
	Items.push_back(text);
	SelectedIndex = 0;
}

void CComboBox::OnUpdate()
{
	if (IsOpen)
	{
		m_iHeight = 16 + 16 * Items.size();

		/*if (parent->GetFocus() != this)
		IsOpen = false;*/
	}
	else
	{
		m_iHeight = 16;
	}

}

void CComboBox::OnClick()
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 16 };

	if (IsOpen)
	{
		// If we clicked one of the items(Not in the top bar)
		if (!GUI.IsMouseInRegion(Region))
		{
			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 16 + i * 16, m_iWidth, 16 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					SelectedIndex = i;
				}
			}
		}

		// Close the drop down
		IsOpen = false;
	}
	else
	{
		IsOpen = true;
	}
}

int CComboBox::GetIndex()
{
	return SelectedIndex;
}

std::string CComboBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "Error";
}

void CComboBox::SelectIndex(int idx)
{
	if (idx >= 0 && idx < Items.size())
	{
		SelectedIndex = idx;
	}
}

#pragma endregion Implementations of the ComboBox functions

#pragma region ComboBox2
CComboBox2::CComboBox2()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_ComboBox;
	winWidth = 400;
	winHeight = 400;
}

void CComboBox2::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };
	Render::Outline(a.x, a.y, m_iWidth, 20, Color(2, 2, 2, 255));
	Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, 16, Color(35, 35, 35, 255), Color(35, 35, 35, 255));

	// Hover for the Top Box
	if (GUI.IsMouseInRegion(Region))
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, 16, Color(40, 40, 40, 255), Color(40, 40, 40, 255));

	// If we have some items
	if (Items.size() > 0)
	{
		// The current item
		RECT txtSize = Render::GetTextSize(Render::Fonts::Menu, GetItem().c_str());
		Render::Text(a.x + 4, a.y + (Region.bottom / 2) - (txtSize.bottom / 2), Color(244, 244, 244, 255), Render::Fonts::Menu, GetItem().c_str());

		// If the drop down part is open
		if (IsOpen)
		{
			if (Menu::Window.IsOpen())
			{
				/*Render::Clear(
				(Menu::Window.get_x() + 8 - 200 + Menu::Window.get_iWidth() + 8 - 200) / 2 - (winWidth / 2),
				(Menu::Window.get_y() + 1 + 28 * 2) + (Menu::Window.get_iHeight() + 1 + 28) * 2 / 2 - (winHeight / 2),
				winWidth,
				winHeight,
				Color(45,45,45,255));*/
			}

			Render::GradientV(a.x, a.y + 20, m_iWidth, Items.size() * 16, Color(35, 35, 35, 255), Color(35, 35, 35, 255));

			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 17 + i * 16, m_iWidth, 16 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					Render::GradientV(a.x + 2, a.y + 20 + i * 16, m_iWidth - 4, 16, Color(40, 40, 40, 255), Color(40, 40, 40, 255));
				}

				Render::Text(a.x + 4, a.y + 19 + i * 16 - 1 + 4, Color(244, 244, 244, 255), Render::Fonts::Menu, Items[i].c_str());
			}
			Render::Outline(a.x, a.y + 20, m_iWidth, Items.size() * 16, Color(2, 2, 2, 255));
		}
	}
	Vertex_t Verts2[3];
	Verts2[0].m_Position.x = a.x + m_iWidth - 10;
	Verts2[0].m_Position.y = a.y + 8;
	Verts2[1].m_Position.x = a.x + m_iWidth - 5;
	Verts2[1].m_Position.y = a.y + 8;
	Verts2[2].m_Position.x = a.x + m_iWidth - 7.5;
	Verts2[2].m_Position.y = a.y + 11;

	Render::Polygon(3, Verts2, Color(2, 2, 2, 255));
}

void CComboBox2::AddItem(std::string text)
{
	Items.push_back(text);
	SelectedIndex = 0;
}

void CComboBox2::OnUpdate()
{
	if (IsOpen)
	{
		m_iHeight = 16 + 16 * Items.size();

		if (parent->GetFocus() != this)
			IsOpen = false;
	}
	else
	{
		m_iHeight = 16;
	}

}

void CComboBox2::OnClick()
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 16 };

	if (IsOpen)
	{
		// If we clicked one of the items(Not in the top bar)
		if (!GUI.IsMouseInRegion(Region))
		{
			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 16 + i * 16, m_iWidth, 16 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					SelectedIndex = i;
				}
			}
		}

		// Close the drop down
		IsOpen = false;
	}
	else
	{
		IsOpen = true;
	}

}

int CComboBox2::GetIndex()
{
	return SelectedIndex;
}

void CComboBox2::SetIndex(int index)
{
	SelectedIndex = index;
}

std::string CComboBox2::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "Error";
}

void CComboBox2::SelectIndex(int idx)
{
	if (idx >= 0 && idx < Items.size())
	{
		SelectedIndex = idx;
	}
}

#pragma endregion Implementations of the ComboBox2 functions

//////////////////////////////////////////////////////////////

char* KeyDigits[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };


CTextField::CTextField()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

std::string CTextField::getText()
{
	return text;
}

void CTextField::SetText(std::string stext)
{
	text = stext;
}

void CTextField::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(53, 53, 53, 255));
	if (hover || IsGettingKey)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(53, 53, 53, 255));

	const char *cstr = text.c_str();

	Render::Text(a.x + 2, a.y + 2, Color(255, 255, 255, 255), Render::Fonts::MenuBold, cstr);
}

void CTextField::OnUpdate()
{
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	POINT b;
	const char *strg = text.c_str();

	if (IsGettingKey)
	{
		b = GetAbsolutePos();
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT)
				{
					IsGettingKey = false;
					return;
				}

				if (i == VK_BACK && strlen(strg) != 0)
				{
					text = text.substr(0, strlen(strg) - 1);
				}

				if (strlen(strg) < 6 && (i == 0x30 || i == 0x31 || i == 0x32 || i == 0x33 || i == 0x34 || i == 0x35 || i == 0x36 || i == 0x37 || i == 0x38 || i == 0x39 || i == VK_NUMPAD0 || i == VK_NUMPAD1 || i == VK_NUMPAD2 || i == VK_NUMPAD3 || i == VK_NUMPAD4 || i == VK_NUMPAD5 || i == VK_NUMPAD6 || i == VK_NUMPAD7 || i == VK_NUMPAD8 || i == VK_NUMPAD9))
				{
					text = text + KeyDigits[i];
					return;
				}
			}
		}
	}
}

void CTextField::OnClick()
{
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

#pragma endregion Implementation of the Textfield

#pragma region TextField2

char* KeyDigitss[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CTextField2::CTextField2()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

std::string CTextField2::getText()
{
	return text;
}

void CTextField2::SetText(std::string stext)
{
	text = stext;
}

void CTextField2::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(53, 53, 53, 255));
	if (hover || IsGettingKey)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(53, 53, 53, 255));

	const char *cstr = text.c_str();

	Render::Text(a.x + 2, a.y + 2, Color(255, 255, 255, 255), Render::Fonts::MenuBold, cstr); //??? geht das jetzt mit cstr oder was
}

void CTextField2::OnUpdate()
{
	POINT a = GetAbsolutePos();
	POINT b;
	m_iHeight = 16;
	const char *strg = text.c_str();

	if (IsGettingKey)
	{
		b = GetAbsolutePos();
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT)
				{
					IsGettingKey = false;
					return;
				}

				if (i == VK_BACK && strlen(strg) != 0)
				{
					text = text.substr(0, strlen(strg) - 1);
				}

				if (strlen(strg) < 20 && i != NULL && KeyDigitss[i] != nullptr)
				{
					text = text + KeyDigitss[i];
					return;
				}

				if (strlen(strg) < 20 && i == 32)
				{
					text = text + " ";
					return;
				}
			}
		}
	}
}

void CTextField2::OnClick()
{
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

#pragma endregion Implementation of the Textfield2

#define LIST_ITEM_HEIGHT 16
#define LIST_SCROLL_WIDTH 16

#pragma region ListBox
CListBox::CListBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	SelectedIndex = 0;
}

void CListBox::Draw(bool hover)
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight + 2, UI_COL_CLIENTBACK);

	if (Items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < Items.size() && drawnItems < ItemsToDraw); i++)
		{
			Color textColor = UI_COL_TABTEXT;
			RECT ItemRegion = { a.x + 1, a.y + 1 + drawnItems * 16, m_iWidth - LIST_SCROLL_WIDTH - 2 , 16 };

			if (i == SelectedIndex)
			{
				textColor = COL_WHITE;
				int CheckBoxR = 155;
				int CheckBoxG = 255;
				int CheckBoxB = 50;
				Render::Clear(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, Color(CheckBoxR, CheckBoxG, CheckBoxB));
			}
			else if (GUI.IsMouseInRegion(ItemRegion))
			{
				textColor = COL_WHITE;
				Render::Clear(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, UI_COL_TABTEXT);
			}

			Render::Text(ItemRegion.left + 4, ItemRegion.top + 2, textColor, Render::Fonts::MenuBold, Items[i].c_str());
			drawnItems++;
		}

		// Ratio of how many visible to how many are hidden
		float sizeRatio = float(ItemsToDraw) / float(Items.size());
		if (sizeRatio > 1.f) sizeRatio = 1.f;
		float posRatio = float(ScrollTop) / float(Items.size());
		if (posRatio > 1.f) posRatio = 1.f;

		sizeRatio *= m_iHeight;
		posRatio *= m_iHeight;

		Render::Clear(a.x + m_iWidth - LIST_SCROLL_WIDTH, a.y + posRatio, LIST_SCROLL_WIDTH, sizeRatio, UI_COL_TABTEXT);
	}

}

void CListBox::AddItem(std::string text, int value)
{
	Items.push_back(text);
	Values.push_back(value);
}

void CListBox::OnClick()
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	// Check the items
	if (Items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < Items.size() && drawnItems < ItemsToDraw); i++)
		{
			Color textColor = UI_COL_TABTEXT;
			RECT ItemRegion = { a.x + 1, a.y + 1 + drawnItems * 16, m_iWidth - LIST_SCROLL_WIDTH - 2 , 16 };
			if (GUI.IsMouseInRegion(ItemRegion))
			{
				SelectItem(i);
				return;
			}
			drawnItems++;
		}
	}

	// Scrollbar checks are in update so we can just drag

}

void CListBox::OnUpdate()
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	// Did we click in the scrollbar??
	RECT Scroll = { a.x + m_iWidth - LIST_SCROLL_WIDTH , a.y + 1, LIST_SCROLL_WIDTH - 2 ,m_iHeight };
	if (GUI.IsMouseInRegion(Scroll) && GUI.GetKeyState(VK_LBUTTON))
	{
		// Ratio of how many visible to how many are hidden
		float ratio = float(ItemsToDraw) / float(Items.size());
		POINT m = GUI.GetMouse();
		m.y -= a.y;

		float sizeRatio = float(ItemsToDraw) / float(Items.size());
		sizeRatio *= m_iHeight;
		float heightDelta = m.y + sizeRatio - m_iHeight;
		if (heightDelta > 0)
			m.y -= heightDelta;

		float mPosRatio = float(m.y) / float(m_iHeight);
		ScrollTop = mPosRatio*Items.size();
		if (ScrollTop < 0)
			ScrollTop = 0;

	}
}

void CListBox::SetHeightInItems(int items)
{
	m_iHeight = items*LIST_ITEM_HEIGHT;
}

std::string CListBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "Error";
}


#pragma endregion Implementations of the ListBox functions

