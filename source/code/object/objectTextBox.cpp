#include "object.h"

void Object::SetTextBox(std::shared_ptr<Object> obj) { textBoxPtr = obj; }

std::shared_ptr<C_TextBox> Object::GetTextBoxComponent() {
	if (!textBoxPtr) {
		Logger::error("class Object", __func__, "Trying to set textBox string while textBox is null");
		return nullptr;
	}
	auto textBoxComponent = textBoxPtr->GetComponent<C_TextBox>();
	if (!textBoxPtr) {
		Logger::error("class Object", __func__, "Trying to set textBox string while textBox component isn't set");
		return nullptr;
	}
	return textBoxComponent;
}


bool Object::IsTextBoxDone() {
	auto textBoxComponent = GetTextBoxComponent();
	return (textBoxComponent) ? textBoxComponent->IsDone() : false;
}
void Object::SetTextBoxString(std::string str) {
	auto textBoxComponent = GetTextBoxComponent();
	if (!textBoxComponent)
		return;
	textBoxComponent->SetStrToPrint(str);
}

void Object::EnableTextBox() {
	if (!textBoxPtr) {
		Logger::error("class Object", __func__, "Trying to enable null textBox");
		return;
	}

	textBoxPtr->SetOn();
}
void Object::DisableTextBox() {
	if (!textBoxPtr) {
		Logger::error("class Object", __func__, "Trying to enable null textBox");
		return;
	}

	textBoxPtr->SetOff();
}
