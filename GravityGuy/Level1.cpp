/**********************************************************************************
// Level1 (C?digo Fonte)
// Descri??o:   N?vel 1 do jogo
//
**********************************************************************************/

#include "Mabel.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include "Thorn.h"
#include "Food.h"
#include "Decoration.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est?ticos da classe

Scene* Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	// cria gerenciador de cena
	scene = new Scene();
	Mabel::player->Reset();
	// pano de fundo do jogo
	backg = new Background(Color{ 1,1,1,1 });
	scene->Add(backg, STATIC);

	// adiciona jogador na cena
	
	scene->Add(Mabel::player, MOVING);

	// ----------------------
	// plataformas
	// ----------------------

	Platform* plat;
	float posX, posY;
	uint  platType;
	Color white{ 1,1,1,1 };
	/*
	plat = new Platform(0, 0, SMALL, white);
	scene->Add(plat, STATIC);
	*/


	//Thorn* thorn = new Thorn(1000.0f, 546.0f, white);
	Thorn* thorn;
	//scene->Add(thorn, STATIC);

	
	ifstream fin;
	fin.open("Level1.txt");

	fin >> posX;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// l? linha com informa??es da plataforma
			fin >> posY; fin >> platType;
			plat = new Platform(posX, posY, platType, white);
			scene->Add(plat, STATIC);
		}
		else
		{
			// ignora coment?rios
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}

		fin >> posX;
	}
	fin.close();

	
	// ----------------------

	// inicia com m?sica
	Mabel::audio->Frequency(MUSIC, 0.94f);
	//Mabel::audio->Frequency(MUSIC, 0.94f);
	Mabel::audio->Frequency(TRANSITION, 1.0f);
	Mabel::audio->Frequency(SCORE_POINT, 1.25f);
	Mabel::audio->Volume(TRANSITION, 0.50f);
	Mabel::audio->Volume(SCORE_POINT, 1.1f);
	Mabel::audio->Play(MUSIC);


	sysFont = new Font("Resources/ink-free32.png");
	sysFont->Spacing("Resources/ink-free32.dat");
	gameFont = new Font("Resources/ink-free32.png");
	gameFont->Spacing("Resources/ink-free32.dat");



	Food* food;
	

	fin.open("Level1Food.txt");
	fin >> posX;

	while (!fin.eof())
	{
		if (fin.good())
		{
			// l? linha com informa??es da plataforma
			fin >> posY;
			food = new Food(posX, posY, white);
			scene->Add(food, STATIC);
		}
		else
		{
			// ignora coment?rios
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}

		fin >> posX;
	}
	fin.close();

	int obsType = 0;
	fin.open("Level1Obstacles.txt");
	fin >> posX;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// l? linha com informa??es da plataforma
			fin >> posY;
			fin >> obsType;
			if (obsType == 0) {
				thorn = new Thorn(posX, posY, Color(1,.6f,.6f,1));
				scene->Add(thorn, STATIC);

			}
			
		}
		else
		{
			// ignora coment?rios
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}

		fin >> posX;
	}
	fin.close();
	
	Decoration* decoration = new Decoration(18500,380, FINISH_LINE,white,.56f);
	scene->Add(decoration, STATIC);
	

	//Mabel::totalScore = 0;
	Mabel::scene = scene;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	if (window->KeyPress(VK_ESCAPE))
	{
		Mabel::audio->Stop(MUSIC);
		Mabel::NextLevel<Home>();
		Mabel::player->Reset();
	}
	/*else if (Mabel::player->Bottom() < 0 || Mabel::player->Top() > window->Height())
	{
		Mabel::audio->Stop(MUSIC);
		Mabel::NextLevel<GameOver>();
		Mabel::player->Reset();

	}*/

	else if (Mabel::player->Top() > window->Height())
	{
		Mabel::totalScore += Mabel::player->score;
		if (Mabel::totalScore > Mabel::highScore) {
			Mabel::highScore = Mabel::totalScore;
		}
		Mabel::audio->Stop(MUSIC);
		Mabel::NextLevel<GameOver>();
		Mabel::player->Reset();
	}
	else if (Mabel::player->Level() == 1 || window->KeyPress('N'))
	{
		Mabel::totalScore = Mabel::player->score;
		if (Mabel::totalScore > Mabel::highScore) {
			Mabel::highScore = Mabel::totalScore;
		}
		Mabel::NextLevel<Level2>();
		Mabel::player->Reset();

	}
	else
	{
		scene->Update();
		scene->CollisionDetection();
	}
	if (Mabel::player->die) {
		Mabel::audio->Stop(MUSIC);
		Mabel::NextLevel<GameOver>();
		Mabel::player->Reset();
	}

}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	backg->Draw();
	scene->Draw();


	text.str("");
	//text << "1000";
	text<< "Score: " << Mabel::player->score;

	int length = int(text.tellp());
	gameFont->Draw(window->Width()-200.0f, 35.0f, "Level 1/2", Color(0, 0, 0, 1));
	gameFont->Draw(window->Width() - (16.0f * length)-50.0f, 75.0f, text.str(), Color(0, 0, 0, 1));
	if (Mabel::viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	scene->Remove(Mabel::player, MOVING);
	delete scene;
	delete sysFont;
	delete gameFont;
	
}

// ------------------------------------------------------------------------------
