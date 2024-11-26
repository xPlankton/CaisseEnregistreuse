#include "section.hpp"

Section::Section(QBoxLayout* parent, QFrame::Shape shape){
    frame = new QFrame();
    frame->setFrameShadow(QFrame::Plain);
    frame->setFrameShape(shape);
    parent->addWidget(frame);
    parent->setSpacing(0);
}
void Section::addWidget(QWidget* widget){
    layout->addWidget(widget);
}
VSection::VSection(QBoxLayout* parent, QFrame::Shape shape) : Section(parent, shape){
    layout = new QVBoxLayout(frame);
}
VSection::VSection(Section parent, QFrame::Shape shape) : Section(parent.layout, shape){
    layout = new QVBoxLayout(frame);
}
HSection::HSection(QBoxLayout* parent, QFrame::Shape shape) : Section(parent, shape){
    layout = new QHBoxLayout(frame);
}
HSection::HSection(Section parent, QFrame::Shape shape) : Section(parent.layout, shape){
    layout = new QHBoxLayout(frame);
}
