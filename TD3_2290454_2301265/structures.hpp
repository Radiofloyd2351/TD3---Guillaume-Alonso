#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <cassert>
#include "gsl/span"
#include <memory>
#include <functional>
using gsl::span;
using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront définis après.



class ListeActeurs {
public:
	int capacite, nElements;
	std::unique_ptr<Acteur[]> elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
	ListeActeurs(int capacite) : capacite(capacite), nElements(0), elements(make_unique<Acteur[]>(capacite)) {}
};

struct Film
{
	std::string titre = "";
	std::string realisateur = ""; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0;
	int recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs{ 10 };
};

struct Acteur
{
	std::string nom = "";
	int anneeNaissance = 0;
	char sexe = ' ';
	//ListeFilms joueDans;
	std::vector<std::shared_ptr<Film>> films;
};

class ListeFilms {
public:
	ListeFilms() = default;
	ListeFilms(const std::string& nomFichier);
	ListeFilms(const ListeFilms& l) { assert(l.elements == nullptr); } // Pas demandé dans l'énoncé, mais on veut s'assurer qu'on ne fait jamais de copie de liste, car la copie par défaut ne fait pas ce qu'on veut.  Donc on ne permet pas de copier une liste non vide (la copie de liste vide est utilisée dans la création d'un acteur).
	~ListeFilms();
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	Acteur* trouverActeur(const std::string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }
	Film* chercherFilm(std::function <bool(const Film&)> critere) const;

private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
	bool possedeLesFilms_ = false; // Les films seront détruits avec la liste si elle les possède.
};