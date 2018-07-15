/*

Module : trajectoire_ecran.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-15
*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include "trajectoire_ecran.h"

t_trajectoire_ecran init_trajectoire_ecran(void)
{
	return t_trajectoire_ecran();
}

int taille_trajectoire_ecran(const t_trajectoire_ecran * traj)
{
	return 0;
}

int trajectoire_ecran_vide(const t_trajectoire_ecran * traj)
{
	return 0;
}

void set_iter_debut(t_trajectoire_ecran * traj)
{
}

t_point_ecran get_point_iter(t_trajectoire_ecran * traj)
{
	return t_point_ecran();
}

int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt)
{
	return 0;
}

int defiler_point_ecran(t_trajectoire_ecran * traj, t_point_ecran * pt)
{
	return 0;
}

int lire_trajectoire_ecran(t_trajectoire_ecran * traj)
{
	return 0;
}

void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur)
{
}

int liberer_trajectoire_ecran(t_trajectoire_ecran * traj)
{
	return 0;
}

t_groupe_traj_ecran init_groupe(int taille)
{
	return t_groupe_traj_ecran();
}

int get_nombre_traj_groupe(const t_groupe_traj_ecran * groupe)
{
	return 0;
}

int get_taille_groupe(const t_groupe_traj_ecran * groupe)
{
	return 0;
}

t_trajectoire_ecran consulter_groupe(const t_groupe_traj_ecran * groupe, int position)
{
	return t_trajectoire_ecran();
}

int ajouter_traj_groupe(t_groupe_traj_ecran * groupe, t_trajectoire_ecran * traj)
{
	return 0;
}

int vider_traj_groupe(t_trajectoire_ecran * traj)
{
	return 0;
}
