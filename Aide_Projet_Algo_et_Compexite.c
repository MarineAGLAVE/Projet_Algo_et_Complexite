//======================================================================
// UPGMA (Unweighted Pair Group Method with Arithmetic mean):
// Construction d'arbre phylogénétique de façon itérative.
//
// IN: matrice de distance entre les gènes d'intérêts
// OUT: dessin de l'arbre avec parenthèses
//======================================================================


// Création d’une matrice de taille spécifiée (Fig3) ==================
float **nouvelle_matrice(int lignes, int colonnes){
	float **matrice = (float **) malloc(lignes * sizeof(float *));
	if (matrice == NULL) {
		fprintf(stderr, "Memoire insuffisante.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < lignes; i++) {
		matrice[i] = (float *) malloc(colonnes * sizeof(float));
		if (matrice[i] == NULL) {
			fprintf(stderr, "Memoire insuffisante.\n");
			exit(EXIT_FAILURE);
		}
	}
	return matrice;
}


// Algorithme UPGM en pseudo-code ======================================
Entree : une matrice de distances M de taille n×n
Sortie : un arbre phylogénétique raciné avec n feuilles

	DEBUT
	
	arbre := nouvel_arbre()
	racines := nouvelle_liste()
	// Création des feuilles de l’arbre
	pour i allant de 0 à n-1 faire{
		nœudi := nouveau_noeud(i)
		ajout_element_fin(racines, nœudi)
	}finpour
	
	pour k allant de 0 à n-2 faire{
		(i,j) := position de la plus petite valeur de M
		// Création du nouveau nœud nœudn+k
		nœudn+k := nouveau_noeud(n+k)
		nœudn+k→gauche := Element(racines, i)
		nœudn+k→droit := Element(racines, j)
		ajout_element_fin(racines, nœudn+k)
		// Mise `a jour de M avec le nouveau nœud
		M := mise_a_jour(M, n-k, i, j)
		supp_element(racines, j)
		supp_element(racines, i)
	}finpour
	
	root := nouveau_noeud(n+k)
	root→gauche := Element(racines, 0)
	root→droit :=  Element(racines, 1)
	arbre→racine := root
	retourner arbre
	
	FIN
// Algorithme UPGM en vrai? ======================================
Entree : une matrice de distances M de taille n×n
Sortie : un arbre phylogénétique raciné avec n feuilles
UPGM(une matrice de distances M de taille n×n){
	
	arbre = nouvel_arbre();
	racines = nouvelle_liste();
	// Création des feuilles de l’arbre <-> liste de pointeurs pointant vers les noeuds/feuilles
	for (i=0, i<=n-1, i++){
		nœudi = nouveau_noeud(i);
		ajout_element_fin(racines, nœudi);
	}
	
	for (k=0, k<=n-2, k++){
		(i,j) := position de la plus petite valeur de M;
		// Création du nouveau nœud nœudn+k
		nœudn+k = nouveau_noeud(n+k);
		nœudn+k->gauche = Element(racines,i);
		nœudn+k->droit = Element(racines,j);
		ajout_element_fin(racines,nœudn+k);
		// Mise `a jour de M avec le nouveau nœud
		M = mise_a_jour(M,n-k,i,j);
		supp_element(racines,j);
		supp_element(racines,i);
	}
	
	root = nouveau_noeud(n+k);
	root->gauche = Element(racines, 0);
	root->droit =  Element(racines, 1);
	arbre->racine = root;
	retourner arbre;
	
	FIN
// STRUCTURES ==========================================================
// TP2:
typedef struct Maillon Maillon;
typedef struct Liste Liste;

struct Maillon {
    Maillon *suivant;
    Maillon *noeud; //J'ai modif ici pour que ça pointe sur le noeud
};

struct Liste {
    Maillon *tete;
};
//TP3:
typedef struct Noeud Noeud;

struct Noeud {
    int cle;
    struct Noeud *gauche;
    struct Noeud *droit;
};

typedef struct Arbre {
    Noeud *racine;
} Arbre;

// INCLUDE =============================================================

#include <stdio.h>
#include <stdlib.h>

// FONCTIONS A FAIRE ===================================================

//nouvel_arbre (TP3)
/* Cree un nouvel arbre binaire et renvoie un pointeur vers cet arbre */
Arbre *nouvel_arbre() {
    Arbre *arbre=(Arbre *) malloc(sizeof(arbre));
    if(arbre==NULL)     //si pas d'arbre
    {
        fprintf(stderr,"ERREUR ALLOCATION ARBRE.\n");
        exit(1);
    }
    arbre->racine=NULL;
    return arbre;
}

// ===================================================
//nouveau_noeud (TP3)
/* Cree un nouveau noeud et renvoie un pointeur vers ce noeud */
Noeud *nouveau_noeud(int val) {
    
    Noeud *noeud=(Noeud *) malloc(sizeof(noeud));
    if(noeud==NULL)     //si pas de noeud
    {
        fprintf(stderr,"ERREUR ALLOCATION NOEUD.\n");
        exit(1);
    }
    noeud->gauche=NULL;
    noeud->droit=NULL;
    noeud->cle=val;
    
    return noeud;
}

// ===================================================
//nouvelle_liste (TP2)
/* crée une nouvelle liste */
Liste *nouvelle_liste() {
    Liste *liste=(Liste *) malloc(sizeof(liste));
    if(liste==NULL)     //<-> if(!liste) si pas de liste
    {
        fprintf(stderr,"ERREUR ALLOCATION LISTE.\n");
        exit(1);
    }
    liste->tete=NULL;
    return liste;
}
// ===================================================
//~ //nouveau_maillon
//~ /* crée un nouveau maillon qui a pour valeur l'entier val */
//~ Maillon *nouveau_maillon(int val) {
    //~ Maillon *maillon=(Maillon *) malloc(sizeof(maillon));
    //~ if(maillon==NULL)     //if(!maillon)
    //~ {
        //~ fprintf(stderr,"ERREUR ALLOCATION MAILLON.\n");
        //~ exit(1);
    //~ }
    //~ maillon->suivant=NULL;
    //~ maillon->valeur=val;
    
    //~ return maillon;
//~ }
// ===================================================
//ajout_element_fin (TP2)
/* ajoute un élément de valeur val à la fin de la liste */
void ajout_element_fin(Liste *L, int val) {
    if(L==NULL)return;    //void ne retourne rien, mais "return" permet de ne pas continuer la fonction si la liste est déjà vide
    Maillon *q=nouveau_maillon(val);
    if (L->tete== NULL){
        L->tete = q;
    }    
    else{
        Maillon *p=L->tete;
        while(p->suivant!=NULL)      //tant que p-suivant non NULL (donc pas arrivé à la fin)
        {
            p=p->suivant;
        }
        p->suivant=q;
    }
}

// ===================================================
//supp_element (TP2) (à adapter pour que les positions commencent à 0 et non à 1)
/* supprime le k-ième élément de la liste (on suppose que la première place est
 * 1); si c'est possible, on modifie la liste et on renvoie la valeur 1; sinon,
 * on ne modifie pas la liste et on renvoie la valeur 0 */
int supp_element(Liste *L, int k) {
    Maillon *P1 = L->tete;
    if (k==0){
		L->tete = NULL;               // Je l'ai adapté pour que les positions commencent à 0
		free(P1);                     //A TESTER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else{
		i=0;
		while(i<=k-2)&&(p->suivant!=NULL){
			P1=P1->suivant;
			i++;
		}
		Maillon *P2 = P1->suivant;
		P1 = P2->suivant;
		free(P2);
	}
}

// ===================================================
//Element (L:liste chaînée (IN), i:entier (IN), OUT: noeud pointé par iième maillon de L ou NULL s'il n'existe pas)

// ===================================================
//mise_a_jour (M: matrice de distance(IN), OUT: nouvelle matrice de distance)

// ===================================================
//fonction recherche de la position de la plus petite valeur de la matrice M (M:matrice (IN), OUT:(i,j))

