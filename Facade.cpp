#include "Facade.h"

void Facade::facade()
{

	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Pieces
	Pieces mPieces;

	// Board
	Board mBoard(&mPieces, mScreenHeight);

	// Game
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

	// Get the actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	//Creates start menu
	Start_menu s;
	Pause_menu p;

	s.Start_Menu(mIO);

	// ----- Main Loop -----
	
	while (!mIO.IsKeyDown(SDLK_ESCAPE))
	{
		// ----- Draw -----

		mIO.ClearScreen(); 		// Clear screen
		mGame.DrawScene();			// Draw staff
		mIO.UpdateScreen();		// Put the graphic context in the screen

		// ----- Input -----

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
		case (SDLK_RIGHT):
		case (SDLK_d):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX++;
			break;
		}

		case (SDLK_LEFT):
		case (SDLK_a):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX--;
			break;
		}

		case (SDLK_DOWN):
		case (SDLK_s):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				mGame.mPosY++;
			break;
		}

		case (SDLK_x):
		{
			// Check collision from up to down
			while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

			mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

			mBoard.DeletePossibleLines();

			if (mBoard.IsGameOver())
			{
				mIO.Getkey();
				exit(0);
			}

			mGame.CreateNewPiece();

			break;
		}

		case (SDLK_z):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
				mGame.mRotation = (mGame.mRotation + 1) % 4;

			break;
		}
		case (SDLK_c):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation - 1) % 4))
				mGame.mRotation = (mGame.mRotation - 1) % 4;

			break;
		}
		case (SDLK_p):
		{
			int counter = 0; 
			

			if (counter == 0) {
				counter++;
				p.Pause_Menu(mIO);
			}

			break;
		}

		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}
}


