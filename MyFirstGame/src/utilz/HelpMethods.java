package utilz;

import main.Game;

public abstract class HelpMethods {
	
	public static boolean CanMoveHere(float x, float y, float w, float h, int[][]lvlData) {
		
		//Se estiver dentro da tela
		if(x> 0 && x + w < Game.WIDTH_GAME_DIMENSION && y> 0 && y + h <Game.HEIGHT_GAME_DIMENSION) {
			//Se não tiver um objeto
			if(lvlData[(int) (x + w) / Game.TILES_SIZE][(int) (y + h) / Game.TILES_SIZE] < 100 && lvlData[(int) (x) / Game.TILES_SIZE][(int) (y) / Game.TILES_SIZE] < 100)
				return true;
		}
		
		return false;
	}
}
