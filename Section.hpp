#ifndef SECTION_H
#define SECTION_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
struct Section{
    QBoxLayout* layout;
    QFrame* frame;
    Section(QBoxLayout* parent, QFrame::Shape);
    virtual ~Section() = default;
    void addWidget(QWidget* widget);
};
struct HSection : Section{
    HSection(QBoxLayout* parent, QFrame::Shape = QFrame::Box);
    HSection(Section parent, QFrame::Shape = QFrame::Box);
};
struct VSection : Section{
    VSection(QBoxLayout* parent, QFrame::Shape = QFrame::Box);
    VSection(Section parent, QFrame::Shape = QFrame::Box);
};

#endif // SECTION_H
