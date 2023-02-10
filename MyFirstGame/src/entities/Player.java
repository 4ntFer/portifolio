package entities;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import main.Game;
import utilz.LoadSave;
import static utilz.HelpMethods.CanMoveHere;

import static main.Game.TILES_SIZE;

public class Player extends Entity{
	private final static String PLAYER_SPRITES_FILE = "JoelGameSprites.png";
	
	private final static int RUNNING = 0;
	private final static int STOPED = 1;
	private final static int ATACKING = 2;
	
	private final static int LEFT_DIRECTION = 0;
	private final static int RIGHT_DIRECTION = 1;
	
	private final static int OG_SIZE = 96;
	private final static int SIZE = TILES_SIZE*5;
	private final static float SCALE = SIZE/OG_SIZE;
	
	private BufferedImage[][] animations;
	private int animationTick = 0, animationSpeed = 40, animationIndex = 0, direction = LEFT_DIRECTION;
	private int playerAction = RUNNING;
	private boolean up = false, down =  false, left = false, right = false;
	private boolean moving = false, atacking = false;
	private float playerSpeed = 2;
	
	private float drawXOffset = 42, drawYOffset = 40;
	
	public Player(float x, float y) {
		super(x,y, SIZE, SIZE);
		loadAnimations();
		initHitbox(x, y,(20)*SCALE,(40)*SCALE);
	}
	
	
	public void render(Graphics g) {
		
		drawPlayerSprite(g);
		//drawHitbox(g);
		
	}
	
	private void drawPlayerSprite(Graphics g) {
		if(direction == LEFT_DIRECTION) {
			g.drawImage(animations[playerAction][animationIndex], (int) (hitbox.x - drawXOffset*SCALE), (int) (hitbox.y - drawYOffset*SCALE), SIZE, SIZE, null);
		}else if(direction == RIGHT_DIRECTION){
			g.drawImage(animations[playerAction][animationIndex], (int) (hitbox.x - drawXOffset*SCALE) + SIZE, (int) (hitbox.y - drawYOffset*SCALE), -SIZE, SIZE, null);
		}
	}
	
	public void update() {
		
		updatePosition();
		updateHitbox();
		updateAnimationTick();
		setAnimation();
		
	}
	
	private void updatePosition() {
		
		moving =  false;
		
		float xSpeed = 0, ySpeed = 0;
		
		if(atacking) {
			
			if(left && !right) {
				xSpeed = playerSpeed/20;
				direction = LEFT_DIRECTION;
				moving =  true;
			}else if(!left && right) {
				xSpeed = -playerSpeed/20;
				direction = RIGHT_DIRECTION;
				moving =  true;
			}
		
			if(up && !down) {
				ySpeed = -playerSpeed/20;
				moving =  true;
			}else if(!up && down) {
				ySpeed = playerSpeed/20;
				moving =  true;
			}
			
		}else {
			
			if(left && !right) {
				xSpeed = playerSpeed;
				direction = LEFT_DIRECTION;
				moving =  true;
			}else if(!left && right) {
				xSpeed = -playerSpeed;
				direction = RIGHT_DIRECTION;
				moving =  true;
			}
		
			if(up && !down) {
				ySpeed = -playerSpeed;
				moving =  true;
			}else if(!up && down) {
				ySpeed = playerSpeed;
				moving =  true;
			}
			
		}
		
		/*if(CanMoveHere(positionX + xSpeed, positionY + ySpeed, width, height, lvlData)) {
			positionX += xSpeed;
			positionY += ySpeed;
		}else if(CanMoveHere(positionX + xSpeed, positionY, width, height, lvlData)) {
			positionX += xSpeed;
		}else if(CanMoveHere(positionX, positionY + ySpeed, width, height, lvlData)) {
			positionY += ySpeed;
		}*/
		
		if(CanMoveHere(hitbox.x + xSpeed, hitbox.y + ySpeed, hitbox.width, hitbox.height, lvlData)) {
			positionX += xSpeed;
			positionY += ySpeed;
		}else if(CanMoveHere(hitbox.x + xSpeed, hitbox.y, hitbox.width, hitbox.height, lvlData)) {
			positionX += xSpeed;
		}else if(CanMoveHere(hitbox.x, hitbox.y + ySpeed, hitbox.width, hitbox.height, lvlData)) {
			positionY += ySpeed;
		}
	}


	private void setAnimation() {
		if(atacking) {
			playerAction = ATACKING;
		}else if(animationIndex == 0){
			if(moving) {
				playerAction = RUNNING;
			}else {
				playerAction = STOPED;
			}
			
		}
		
	}


	public void setDirection(int dir) {
		moving = true;
	}
	
	public void setMoving(boolean mov) {
		moving = mov;
	}
	
	private void updateAnimationTick() {
		
		animationTick++;
		if(animationTick>=animationSpeed) {
			
			animationTick = 0;
			animationIndex++;
			
			if(animationIndex>=getSpritesAmount(playerAction)) {
				animationIndex = 0;
			}
			
		}
		
	}
	
	private int getSpritesAmount(int action) {
		switch(action) {
		
			default:
				return 1;
			
			case RUNNING:
				return 5;
			
			case STOPED:
				return 3;
				
			case ATACKING:
				return 4;
		
		}
	}


	private void  loadAnimations() {
		
		
	
		BufferedImage img = LoadSave.getImage(PLAYER_SPRITES_FILE);
		animations = new BufferedImage[4][6];
		for(int i=0 ; i < animations.length ; i++) {
				 
			for(int j=0 ; j<animations[i].length ; j++) {
				animations[i][j] = img.getSubimage(j*OG_SIZE, i*OG_SIZE, OG_SIZE, OG_SIZE);
			}
				 
		}
			 
		
		
	}


	public void setUp(boolean up) {
		this.up = up;
	}


	public void setDown(boolean down) {
		this.down = down;
	}


	public void setLeft(boolean left) {
		this.left = left;
	}


	public void setRight(boolean right) {
		this.right = right;
	}


	public void atack(int x, int y) {
		
		if(x > (int) positionX + SIZE) {
			direction = LEFT_DIRECTION;
		}else if(x < (int) positionX) {
			direction = RIGHT_DIRECTION;
		}
		setAtacking(true);
	}
	
	public void setAtacking(boolean atack) {
			atacking = atack;
	}
	
	public boolean getAtacking() {
		return atacking;
}


	public void disableDirBooleans() {
		
		setUp(false);
		setDown(false);
		setLeft(false);
		setRight(false);
		
	}
}


