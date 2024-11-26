#include "caisse.hpp"
#include <string>
void Caisse::ajouter(QString desc, QString prix_s, bool taxable){
    try{
        double prix = std::stod(prix_s.toStdString());
        if(prix <= 0){
            throw new std::out_of_range("La valeur doit être positive");
        }
        for(auto& article : articles_){
            if(article.description == desc){
                throw new std::invalid_argument("l'article est déjà dans la liste");
            }
        }
        Article article = {desc, prix, taxable};
        articles_.push_back(article);
        emit updateArticles(articles_);
        updatePrice(prixAvantTaxes_ + prix);
    }
    catch (const std::invalid_argument& e){
        return;
    }
    catch (const std::out_of_range& e){
        return;
    }
}
void Caisse::retirer(int i){
    double elemPrice = articles_[i].prix;
    articles_.erase(articles_.begin() + i);
    emit updateArticles(articles_);
    updatePrice(prixAvantTaxes_-elemPrice);
}
void Caisse::retirerTout(){
    articles_.clear();
    emit updateArticles(articles_);
    updatePrice(0.0);
}
void Caisse::updatePrice(double prixAvantTaxes){
    prixAvantTaxes_ = prixAvantTaxes;
    emit updatePrixAvantTaxes(prixAvantTaxes_);
    double taxes = std::transform_reduce(
        articles_.begin(),
        articles_.end(),
        0.0,
        std::plus{},
        [this](Article article){
            return article.taxable ? article.prix * TAX_FACTOR : 0.0;
        });
    emit updateTax(taxes);
    emit updateTotal(taxes + prixAvantTaxes_);
}
