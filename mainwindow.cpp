#include "mainwindow.hpp"
#include "section.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto mainWidget = new QWidget(this);
    auto mainLayout = new QVBoxLayout(mainWidget);

    auto mainSection = VSection(mainLayout);
    auto title = make_title("Caisse Enregistreuse");
    mainSection.addWidget(title);

    auto secondSection = HSection(mainSection, QFrame::NoFrame);

    auto leftPanel = VSection(secondSection);

    auto rightPanel = VSection(secondSection);
    auto list = new QListWidget();
    rightPanel.addWidget(list);

    auto itemPanelBox = HSection(leftPanel, QFrame::NoFrame);
    auto itemPanel = VSection(itemPanelBox);
    itemPanel.addWidget(make_text("entrez la description de l'article que vous souhaitez rajouter", Qt::AlignHCenter, Qt::AlignVCenter));
    auto itemSubPanel = HSection(itemPanel, QFrame::NoFrame);
    itemSubPanel.addWidget(make_text("article", Qt::AlignHCenter, Qt::AlignVCenter));
    auto article = new QLineEdit();
    itemSubPanel.addWidget(article);

    auto pricePanelBox = HSection(leftPanel, QFrame::NoFrame);
    auto pricePanel = VSection(pricePanelBox);
    pricePanel.addWidget(make_text("entrez le prix de l'article que vous souhaitez rajouter", Qt::AlignHCenter, Qt::AlignVCenter));
    auto priceSubPanel = HSection(pricePanel, QFrame::NoFrame);
    priceSubPanel.addWidget(make_text("prix", Qt::AlignHCenter, Qt::AlignVCenter));
    auto prix = new QLineEdit();
    priceSubPanel.addWidget(prix);
    priceSubPanel.addWidget(make_text("taxable", Qt::AlignHCenter, Qt::AlignVCenter));
    auto taxable = new QCheckBox();
    priceSubPanel.addWidget(taxable);

    auto buttonPanelBox = HSection(leftPanel, QFrame::NoFrame);
    auto buttonPanel = VSection(buttonPanelBox);
    buttonPanel.addWidget(make_button("&Ajouter",
                                      [&, article, prix, taxable](){caisse_.ajouter(article->displayText(),
                                                              prix->displayText(),
                                                              taxable->isChecked());}));
    buttonPanel.addWidget(make_button("&Retirer",
                                      [&, list](){
                                          caisse_.retirer(list->currentRow());

                                      }));
    buttonPanel.addWidget(make_button("Retirer &Tout",
                                      [&](){caisse_.retirerTout();}));

    auto resultPanelBox = HSection(leftPanel, QFrame::NoFrame);
    auto resultPanel = VSection(resultPanelBox);
    resultPanel.addWidget(make_text("Price", Qt::AlignHCenter, Qt::AlignVCenter));

    auto prixSansTaxes = HSection(resultPanel, QFrame::NoFrame);
    prixSansTaxes.addWidget(make_text("Prix", Qt::AlignLeft, Qt::AlignBottom));
    auto prixAvantTaxes = make_text("0.00$", Qt::AlignRight, Qt::AlignBottom);
    prixSansTaxes.addWidget(prixAvantTaxes);

    auto TAX = HSection(resultPanel, QFrame::NoFrame);
    TAX.addWidget(make_text("Taxes", Qt::AlignLeft, Qt::AlignBottom));
    auto taxes = make_text("0.00$", Qt::AlignRight, Qt::AlignBottom);
    TAX.addWidget(taxes);

    auto total = HSection(resultPanel, QFrame::NoFrame);
    total.addWidget(make_text("Total", Qt::AlignLeft, Qt::AlignBottom));
    auto leTotal = make_text("0.00$", Qt::AlignRight, Qt::AlignBottom);
    total.addWidget(leTotal);

    QObject::connect(&caisse_, &Caisse::updateArticles, this,
                     [=](std::vector<Article> articles){
                         updateList(list, articles);
    });
    QObject::connect(&caisse_, &Caisse::updatePrixAvantTaxes, this,
                     [=](double prix){
                         updateLabel(prixAvantTaxes, prix);
    });
    QObject::connect(&caisse_, &Caisse::updateTax, this,
                     [=](double tax){
                         updateLabel(taxes, tax);
                     });
    QObject::connect(&caisse_, &Caisse::updateTotal, this,
                     [=](double total){
                         updateLabel(leTotal, total);
                     });

    setCentralWidget(mainWidget);
}
QLabel* MainWindow::make_title(std::string title){
    auto label = new QLabel(QString::fromStdString(title));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    label->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFCDCB; text-decoration: underline;");
    return label;
}
QLabel* MainWindow::make_text(
    std::string text,
    Qt::AlignmentFlag align1,
    Qt::AlignmentFlag align2)
{
    auto label = new QLabel(QString::fromStdString(text));
    label->setAlignment(align1 | align2);
    return label;
}
template<typename T>
QPushButton* MainWindow::make_button(std::string text, const T& slot){
    auto button = new QPushButton(this);
    button->setText(QString::fromStdString(text));
    if constexpr (!std::is_same_v<T, decltype(nullptr)>){
        QObject::connect(button, &QPushButton::clicked, this, slot);
    }
    return button;
}


void MainWindow::updateList(QListWidget* list, std::vector<Article>& articles){
    list->clear();
    for(auto& article : articles){
        list->addItem(article.description + "\t" + QString::number(article.prix, 'f', 2) + "$\t" + (article.taxable ? "taxable" : ""));
    }
}
void MainWindow::updateLabel(QLabel* label, double number){
    label->setText(QString::number(number, 'f', 2) + QString::fromStdString("$"));
}
