//
// Created by mitue on 07/11/2020.
//

#ifndef CARDGAME_MATCH_H
#define CARDGAME_MATCH_H



#include "Joueur.h"

#include "../../../biblio.h"



class Match {
private:
    std::vector<Joueur> m_joueur;//set de joueur  car pas le meme nom
public:
    //Constructeurs et Destructeurs
    Match();
    Match(Utilisateur *_user1,Utilisateur *_user2,int _numDeck1,int _numDeck2);
    ~Match();
    //Méthodes
    void lancementmatch();

    //Getter et Setter

};


#endif //CARDGAME_MATCH_H
