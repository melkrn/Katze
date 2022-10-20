/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
//
// Descrição:   Fim do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GameOver.h"
#include "Mabel.h"
#include "Home.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
	title = new Sprite("Resources/sky_d.png");
	pressEsc = new TileSet("Resources/esc.png", 480, 62, 1, 5);
	anim1 = new Sprite("Rosources/gameover.png");
	anim2 = new Animation(pressEsc, 0.180f, true);

	gameFont = new Font("Resources/ink-free32.png");
	gameFont->Spacing("Resources/ink-free32.dat");


}

// ----------------------------------------------------------------------

void GameOver::Update()
{
	if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
		Mabel::NextLevel<Home>();
	else
	{

		anim2->NextFrame();

	}
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
	title->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0F, 0.0F,Color(0.1f,0.1f,0.1f,1));
	anim2->Draw(window->CenterX(), window->CenterY() - pressEsc->TileHeight() / 2, Layer::FRONT);
	anim1->Draw(window->CenterX(), window->CenterY() - pressEsc->TileHeight() / 2, Layer::MIDDLE);

	text.str("");
	//text << "1000";
	text << "Total Score: " << Mabel::totalScore;

	int length = int(text.tellp());
	gameFont->Draw(window->CenterX() - (length*16.0f)/2, 600.0f, text.str(), Color(1, 1, 1, .65f));

}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
	Mabel::totalScore = 0;
	delete title;
	delete anim1;
	delete anim2;
	delete pressEsc;
	delete gameFont;
	
}

// ----------------------------------------------------------------------

