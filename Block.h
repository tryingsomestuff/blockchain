#pragma once

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>

/*
Un bloc est simplement une structure contenant son numéro de bloc (index_), de la donnée (data_), un numéro arbitraire appelé NONCE diminutif de Number used ONCE (nonce_), et le hash de toutes ces données (hash_) ainsi que le hash du block précédent (prevHash_). 
Il existe différentes règles de validation d’un bloc selon la blockchain considérée. La plupart des blockchains utilisent une preuve de travail qui consiste a prouver qu’un travail de validation a été effectuée sur le bloc. Par exemple, une règle de validation très utilisée est que le hash doit commencer par un certain nombre de 0. Le bloc va donc devoir être miné, c’est-à-dire qu’il va falloir trouver un NONCE tel que le hash du bloc commence par exemple par '000000'. Notez que ce choix est totalement arbitraire. Les concepteurs d’une blockchain peuvent par exemple choisir que le hash doive commencer par 123 ou que le hash en base 10 soit inférieur à 1000 (cas de l’Ethereum). Il faut simplement une règle qui prouve qu’un travail de validation a été effectué sur le bloc. Quand la règle est validée, le bloc est alors signé.

Dans la fonction mine(), nous allons simplement incrémenter NONCE et recalculer le hash jusqu’à ce que l’on obtienne un hash commençant par 000000. Ce processus n’est pas fixe en temps, il peut être très court ou très long, car chaque essai de NONCE est équiprobable. Une fois cela fait, le hash est valide, le bloc est maintenant signé. Miner consiste donc à calculer le hash encore et encore jusqu’à ce que la règle de validation soit validée. 

Si l’on tente de modifier quoi que ce soit dans un bloc signé, il perd la validité de sa signature, car le hash change et il faudrait de nouveau miner le bloc pour trouver un nouveau hash commençant par 000000. Si le bloc est déjà dans une chaine il faudrait miner à nouveau tous les blocs après ce bloc modifié.
*/
class Block {
  public:
   std::string hash;
   std::string prevHash;

   Block(const uint32_t index, const std::string &data);

   // will fill the block hash
   void mine(const uint32_t difficulty);

   bool isSigned(const uint32_t difficulty) const;

   bool isValid(const uint32_t difficulty) const;

   inline std::string &      data() { return data_; }
   inline const std::string &data() const { return data_; }

  private:
   uint32_t    index_;
   uint32_t    nonce_;
   std::string data_;
   std::chrono::microseconds timeStamp_;

   std::string computeHash_() const;
};
