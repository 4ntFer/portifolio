package entities;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.geom.Rectangle2D;

public abstract class Entity {
	protected float positionX, positionY;
	protected int width, height;
	protected Rectangle2D.Float hitbox; 
	
	protected int[][] lvlData;
	
	public Entity(float x, float y, int h, int w){
		positionX = x;
		positionY = y;
		width = w;
		height = h;
		
	}
	
	protected void initHitbox(float x, float y, float w, float h) {
		hitbox = new Rectangle2D.Float(x,y,w,h);
	}
	
	protected void updateHitbox() {
		hitbox.x = (int) positionX;
		hitbox.y = (int) positionY;
	}
	
	protected void drawHitbox(Graphics g) {
		g.setColor(Color.PINK);
		g.drawRect((int)hitbox.x, (int)hitbox.y, (int)hitbox.width, (int)hitbox.height);
	}
	
	public void loadLvlData(int[][] lvlData) {
		this.lvlData = lvlData;
	}
}