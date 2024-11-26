#ifndef CAISSE_HPP
#define CAISSE_HPP
#include <QObject>
#include "article.hpp"
#include <QString>
#pragma once
class Caisse : public QObject
{
    Q_OBJECT
public:
    Caisse() = default;
    const double TAX_FACTOR = 0.14975;

public slots:
    void ajouter(QString desc, QString prix_s, bool taxable);
    void retirer(int i);
    void retirerTout();

signals:
    void updatePrixAvantTaxes(double prix);
    void updateTax(double tax);
    void updateTotal(double total);
    void updateArticles(std::vector<Article>& articles);

private:
    std::vector<Article> articles_{};
    double prixAvantTaxes_ = 0.0;

    void updatePrice(double factor);
};

#endif // CAISSE_HPP
