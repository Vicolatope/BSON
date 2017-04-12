# BSON

Un parser Bson, realise en CPP.
Le constructeur de ela classe BSON attend un vector<char> et une size en parametres,
Permet ensuite d'acceder aux donnees, ou de les dump en JSON.

RESTE A DEFINIR:
  -Sur BSON:
    -Une methode permettant d'acceder a un document grace a un index,
    -Une methode permettant d'acceder a un tableau de documents grace a une fonction "filtrant" chaque document
    -Une methode map, permettant d'appliquer la fonction a chaque document.
   -Sur chaque BSON_element:
    -Une methode pour set la valeur de l'element en question.
    -Verifier si la representation de data sur certains types (js_code en particulier) et adequate, et que le dump Json est correct pour tous.
