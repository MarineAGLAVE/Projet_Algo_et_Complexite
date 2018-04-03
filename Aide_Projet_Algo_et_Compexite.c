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
	// Création des feuilles de l’arbre
	for (i=0, i<=n-1, i++){
		nœudi = nouveau_noeud(i);
		ajout_element_fin(racines, nœudi);
	}
	
	for (k=0, k<=n-2, k++){
		(i,j) := position de la plus petite valeur de M;
		// Création du nouveau nœud nœudn+k
		nœudn+k = nouveau_noeud(n+k);
		nœudn+k→gauche = Element(racines,i);
		nœudn+k→droit = Element(racines,j);
		ajout_element_fin(racines,nœudn+k);
		// Mise `a jour de M avec le nouveau nœud
		M = mise_a_jour(M,n-k,i,j);
		supp_element(racines,j);
		supp_element(racines,i);
	}
	
	root = nouveau_noeud(n+k);
	root→gauche = Element(racines, 0);
	root→droit =  Element(racines, 1);
	arbre→racine = root;
	retourner arbre;
	
	FIN
// FONCTIONS A FAIRE ===================================================

nouvel_arbre (TP3)
nouveau_noeud (TP3)
nouvelle_liste (TP2)
ajout_element_fin (TP2)
supp_element (TP2) (à adapter pour que  lespositions commencent à 0 et non à 1)
Element (L:liste chaînée (IN), i:entier (IN), OUT: noeud pointé par iième maillon de L ou NULL s'il n'existe pas)
mise_a_jour (M: matrice de distance(IN), OUT: nouvelle matrice de distance)
