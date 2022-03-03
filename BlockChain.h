#pragma once

#include <cstdint>
#include <vector>

#include "Block.h"

/*
Une blockchain simplement d’une liste de blocs pour lesquels chaque bloc contient une référence 
au bloc précédent via le hash. Ils sont donc "chaînées".

On comprend donc que si on change quoi que ce soit dans un bloc, ce bloc et tous les blocs suivants 
perdent leur signature. Il est donc très facile de savoir si la moindre information d’une blockchain 
a été changée et dans quel bloc.

Il est cependant possible de miner à nouveau ces blocs non signés depuis le dernier bloc signé et 
revalider l’ensemble de la chaîne. Mais alors, si on peut resigner les blocs, peut-on altérer une 
blockchain? Non, déjà parce que miner un bloc est très demandeur en puissance de calcul et d’autant 
que plus vous remontez dans le temps et modifiez un bloc ancien et plus vous aurez de blocs à miner.

Pour les cryto-monnaies c’est surtout grâce à son aspect distribué que la blockchain est véritablement sûre.
*/
class BlockChain {
  public:
   BlockChain(const uint32_t difficulty = 0);
   void addBlock(Block&& b);

   Block&       operator[](const size_t index);
   const Block& operator[](const size_t index) const;

   const uint32_t difficulty;

   bool isValidBlock(const size_t index) const;
   bool isValidChain() const;

   inline size_t size() const { return chain_.size(); }

  private:
   static constexpr uint32_t defaultDifficulty_ = 4;
   std::vector<Block>        chain_;

   Block last_() const;
};
