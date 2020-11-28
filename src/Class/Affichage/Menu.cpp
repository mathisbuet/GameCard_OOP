//
// Created by bemat on 24/11/2020.
//

#include "../../Headers/Affichage/Menu.h"

Menu::Menu()
     :Affichage(), m_menuActuel(0), m_boutonActuel("none"),m_erreur(-1),m_gestionUtilisateur("none"),m_mode(0)
{
    m_choixInscription._choixTypeCarte="none";
    m_bool.ancienClick=false;
    m_bool.sleep=false;
    m_bool.fin=false;
    m_bool.ancienEchap=false;


}

Menu::~Menu()
{

}

/*
 * Accesseur et mutateur
 */

void Menu::setMenuActuel(int _menuActuel){
    if(_menuActuel>=-1){
        m_menuActuel=_menuActuel;
    }
}

int Menu::getMenuActuel() const{
    return m_menuActuel;
}

void Menu::setBoutonActuel(const std::string& _boutonActuel){
    m_boutonActuel=_boutonActuel;
}

std::string Menu::getBoutonActuel() const{
    return m_boutonActuel;
}

void Menu::setErreur(int _erreur){
    m_erreur=_erreur;
}

int Menu::getErreur() const{
    return m_erreur;
}

std::string Menu::getGestionUtilisateur() const{
    return m_gestionUtilisateur;
}

void Menu::setGestionUtilisateur(std::string a){
    m_gestionUtilisateur=a;
}

int Menu::getMode() const{
    return m_mode;
}

void Menu::setMode(int _mode){
    if(_mode>=0 && _mode <=1)
        m_mode=_mode;
}

t_booleen Menu::getBool() const{
    return m_bool;
}
/*
 * Méthodes
 */

void Menu::gestionChangementMenu(){
    //Si menu de gestion Utilisateurs
    if(getGestionUtilisateur()!="none")
        setGestionUtilisateur("none");

    else{
        if(getMenuActuel()>=0&&getMenuActuel()<=3)
            setMenuActuel(0);
        else if(getMenuActuel()==4||getMenuActuel()==5){
            if(m_choixInscription._choixTypeCarte!="none")
                m_choixInscription._choixTypeCarte="none";
            else
                setMenuActuel(1);
        }
        else if(getMenuActuel()==6||getMenuActuel()==7)
            setMenuActuel(3);
    }
}

void Menu::gestionInputCarac(sf::Event& event){

    if (event.text.unicode < 128){
        char carac= (event.text.unicode);
        if((carac >='a' && carac<='z')||(carac >='A' && carac<='Z')|| (carac >= '0' && carac<='9')){

            if(getMenuActuel()==5&&m_choixInscription._choixTypeCarte=="none"){
                //Si le pseudo n'est  pas trop grand
                if(m_choixInscription.pseudoInscription.size()<=15){
                    m_choixInscription.pseudoInscription+=carac;
                }
            }
            if(getMenuActuel()==6 || getMenuActuel()==7) {
                if(m_creationCarte.creaCarte[m_creationCarte.section].size()<=10){
                    m_creationCarte.creaCarte[m_creationCarte.section]+=carac;
                }
                else
                {
                    m_creationCarte.creaCarte[m_creationCarte.section]+="";
                }
            }
        }




    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
        if(getMenuActuel()==5){
            if(!m_choixInscription.pseudoInscription.empty()){
                m_choixInscription.pseudoInscription.pop_back();
            }
        }
        if(getMenuActuel()==6 || getMenuActuel()==7){
            if(!m_creationCarte.creaCarte[m_creationCarte.section].empty()){
                m_creationCarte.creaCarte[m_creationCarte.section].pop_back();
            }
        }
        sf::sleep(sf::milliseconds(100));
    }

}

void Menu::menuInit(int& temp){

    if(getMenuActuel()!=temp){
        temp=getMenuActuel();
        switch(getMenuActuel()){
            case 0:
                menu0Init();
                break;
            case 1:
                menu1Init();
                break;
            case 2:
                menu2Init();
                break;
            case 3:
                menu3Init();
                break;
            case 4:
                menu4Init();
                break;
            case 5:
                menu5Init();
                break;
            case 6:
                menu6Init();
                break;
            case 7:
                menu7Init();
                break;
            default:
                break;
        }
    }
}

void Menu::menuBase(std::string& pseudoCouleur){
    //Affichage des menus
    menuBaseAffichage(pseudoCouleur);

    //Si il y a une erreur en cours
    if(getErreur()>=0){
        erreur();
    }
    else {
        //Si on ne reste pas appuyé sur échap
        if(!m_bool.ancienEchap){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (getMenuActuel() != 0) {
                    gestionChangementMenu();
                } else
                    m_bool.fin = true;
            }
        }

        //Si on ne reste pas appuyé sur clique gauche
        if(!m_bool.ancienClick){
            //Interaction des menus
            switch(getMenuActuel()){
                case 0://menu de base
                    menu0Interaction();
                    break;
                case 1://menu avec Insciription connection et lancement partie
                    menu1Interaction();
                    break;
                case 2:// menu avec les regles
                    menu2Interaction();
                    break;
                case 3 : //Parametres
                    menu3Interaction();
                    break;
                case 4 : //Connection
                    menu4Interaction(pseudoCouleur);
                    break;
                case 5:
                    menu5Interaction();
                    break;
                case 6:
                    menu6Interaction();
                    break;
                case 7:
                    menu7Interaction();
                    break;
            }
            if(getMenuActuel()==1||getMenuActuel()==4){

                if(m_jeu.getUsersConnectes().size()>0){

                    interactionPseudoUtilisateurs();
                }
            }

        }

    }
}

void Menu::initIntro(){
    if (!m_intro.soundBuffer.loadFromFile("../Son/IntroSonJeu.ogg"))
        std::cout << "probleme fichier" <<std::endl;
    m_intro.sound.setBuffer(m_intro.soundBuffer);

    m_intro.sound.play();
    m_intro.sound.setVolume(10);
    m_intro.mot = "ECEMON";
    m_intro.pos=0;
}

void Menu::introJeu() {
    afficheImage("IntroJeu");

    for(int i=0; i<m_intro.pos; i++){
        sf::Text texte;
        texte.setString(m_intro.mot[i]);
        texte.setFont(getFonts()[1]);
        texte.setFillColor(sf::Color(198,27,27,255));
        texte.setCharacterSize(200);
        texte.setPosition(450+i*170,300);
        texte.setOutlineColor(sf::Color::Black);
        texte.setOutlineThickness(4);
        m_window.draw(texte);
    }

    if(m_intro.pos==6){
        m_window.draw(chargerTexte("La guerre des planetes",0,sf::Color(24,97,192,255),150,350,500));

    }
    if(m_intro.pos>=7){
        setMode(0);
    }

    m_intro.pos++;

}

void Menu::boucleBase() {//fonction pour initialiser sfml
    std::string pseudoCouleur;
    int temp=-2;
    /*A REMETTRE */
    /*A REMETTRE */
    //initIntro();/*A REMETTRE */
    /*A REMETTRE */
    /*A REMETTRE */

    while (!getBool().fin) {
        getMousePosition();//obliger de le mettre dans la boucle pour réactualiser tout le temps
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();//permet de fermer la fenetre

            gestionInputCarac(event);
        }

        if(getMode()==0)
            menuInit(temp);

        m_window.clear();

        if(getMode()==2)
            introJeu();
        else if(getMode()==0)
            menuBase(pseudoCouleur);
        else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ //POUR L'INSTANT
                setMode(0);
            }
            m_jeu.getAffichageMatch().boucleMatch();
        }


        m_window.display();

        contrerResterAppuye();
        sleep();

    }
}


void Menu::sleep(){
    /*SI INTRO DU JEU*/
    if(getMode()==2){
        if(m_intro.pos!=7)
            sf::sleep(sf::seconds(1));
        else
            sf::sleep(sf::seconds(4));
    }



    else{
        if(getBool().sleep){
            sf::sleep(sf::seconds(2));
            m_bool.sleep=false;
        }
        else
            sf::sleep(sf::milliseconds(10));
    }

}


void Menu::contrerResterAppuye(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        if(!getBool().ancienEchap)
            m_bool.ancienEchap=true;
    }
    else
        m_bool.ancienEchap=false;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!getBool().ancienClick)
            m_bool.ancienClick=true;
    }
    else
        m_bool.ancienClick=false;

}

void Menu::erreur(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        setErreur(-1);
    }
    else{
        afficheImage("Erreur");
        sf::Text texte;
        texte.setPosition(750,530);
        texte.setFont(getFonts()[1]); // choix de la police
        texte.setFillColor(sf::Color(233,233,233,255));//couleur du texte
        texte.setCharacterSize(18); // choix de la taille des caractères exprimée en pixel

        switch(getErreur()){
            case 0 :
                texte.setString(L"Il y a deja 2 personnes connectées");
                break;
            case 2:
                texte.setString(L"Cet utilisateur est deja connecté!");
                break;
            case 3:
                texte.setString(L"Ce pseudo est deja utilisé!");
                break;
            case 4:
                texte.setString(L"Une immatriculation est invalide!");
                break;
            default:
                break;
        }
        m_window.draw(texte);
    }
}


void Menu::menu0Init(){
    setPos(730,415,"Erreur");
    setPos(1439, 550, "Jouer_no");
    setPos(1439, 550, "Jouer_yes");
    setPos(1418, 700, "Regles_no");
    setPos(1418, 700, "Regles_yes");
    setPos(1400, 850, "Quitter_no");
    setPos(1400, 850, "Quitter_yes");
    setPos(50,900,"Parametres_yes");
    setPos(50,900,"Parametres_no");
    setPos(85,202,"rectInscription");
}


void Menu::menu1Init(){
    setPos(500,500,"connecter_yes");
    setPos(500,500,"connecter_no");
    setPos(1400,1000,"LancerPartie_no");
    setPos(1400,1000,"LancerPartie_yes");
    setPos(1020,500,"Inscription_yes");
    setPos(1020,500,"Inscription_no");
    setPos(50,1000,"Retour_no");
    setPos(50,1000,"Retour_yes");

}


void Menu::menu2Init(){
    setPos(50,1000,"Retour_no");
    setPos(50,1000,"Retour_yes");

}


void Menu::menu3Init() {
    setPos(50,1000,"Retour_no");
    setPos(50,1000,"Retour_yes");
}



void Menu::menu4Init(){
    setPos(0,0,"Background_utilisateur");
}

void Menu::menu5Init(){
    m_choixInscription.imm.clear();
    m_choixInscription.pseudoInscription="";
    m_choixInscription._choixTypeCarte="none";
    m_choixInscription.drag.setActif(false);
    m_choixInscription.valide=false;
}

void Menu::menu6Init(){
    m_creationCarte.creaCarte.clear();
    m_creationCarte.section = 3;
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");


}

void Menu::menu7Init(){
    m_creationCarte.creaCarte.clear();
    m_creationCarte.section = 3;
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");
    m_creationCarte.creaCarte.push_back("");
}
