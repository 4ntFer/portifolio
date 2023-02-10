package levels;

import static main.Game.HEIGHT_GAME_DIMENSION;
import static main.Game.WIDTH_GAME_DIMENSION;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import utilz.LoadSave;

public class Level {
	private BufferedImage lvlBackground;
	private int[][] lvlData;
	
	public Level(){
		lvlData = LoadSave.getLvlData("lvlData.png");
		lvlBackground = LoadSave.getImage("cenario.png");
	}
	
	public void draw(Graphics g) {
		g.drawImage(lvlBackground, 0, 0, WIDTH_GAME_DIMENSION, HEIGHT_GAME_DIMENSION, null );
	}
	
	public int[][] getCurrentLvlData(){
		return lvlData;
	}
}
