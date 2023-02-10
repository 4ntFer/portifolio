package levels;

import java.awt.Graphics;

import main.Game;

public class LevelManager {
	private Game game;
	private Level lvl;
	
	public LevelManager(Game game) {
		
		this.game = game;
		lvl = new Level();
		
	}
	
	
	public void draw(Graphics g) {
		lvl.draw(g);
	}

	public void update() {
		
		
	}
	
	public Level getLevel() {
		return lvl;
	}
}
