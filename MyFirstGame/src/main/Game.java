package main;

import java.awt.Graphics;

import entities.Player;
import levels.LevelManager;

public class Game  implements Runnable{
	
	public final static int TILES_DEAFAULT_SIZE = 32;
	public final static float SCALE = 2.0f;
	public final static int TILES_IN_WIDTH = 26;
	public final static int TILES_IN_HEIGHT = 14;
	public final static int TILES_SIZE = (int) (TILES_DEAFAULT_SIZE * SCALE);
	
	public final static int HEIGHT_GAME_DIMENSION = TILES_IN_HEIGHT * TILES_SIZE;
	public final static int WIDTH_GAME_DIMENSION = TILES_IN_WIDTH * TILES_SIZE;
	
	private GameWindow gameWindow;
	private GamePanel gamePanel;
	private Thread gameThread;
	private Player player;
	private LevelManager levelManeger;
	private final int FPS_SET = 120;
	private final int UPS_SET = 200;
	
	public Game() {
		initClasses();
		gamePanel =  new GamePanel(this);
		gameWindow = new GameWindow(gamePanel);
		gamePanel.requestFocus();
		startGameLoop();
		
		
	}
	
	private void initClasses() {
		levelManeger = new LevelManager(this);
		player = new Player(TILES_SIZE , TILES_SIZE);
		player.loadLvlData(levelManeger.getLevel().getCurrentLvlData());
		
		
	}

	private void startGameLoop() {
		
		gameThread = new Thread(this);
		gameThread.start();
		
	}
	
	public void update() {
		levelManeger.update();
		player.update();
	}
	
	public void render(Graphics g) {
		levelManeger.draw(g);
		player.render(g);
	}


	public void run() {
		
		double timePerFrame = 1000000000.0 / FPS_SET; // 1 segundo em nano-segundos divididos pelo fps
		double timePerUpdate = 1000000000.0 / UPS_SET;
		
		long previusTime = System.nanoTime();
		
		double deltaU = 0; //diferença de tempo entre um frame e outro
		double deltaF = 0; //diferença de tempo entre um upadate e outro
		
		int frames = 0;
		int updates = 0;
		
		long lastCheck = System.currentTimeMillis();
		
		while(true) {
			long currentTime = System.nanoTime();
			
			/*Verifica o tempo do ultimo update.
			 Caso o tempo entre o ultimo update e agora for
			 maior que o timePerUpdate (tempo por update definido
			 anteriormente) então é necessário um novo update.*/
			
			deltaU += (currentTime - previusTime) / timePerUpdate; 
			deltaF += (currentTime - previusTime) / timePerFrame;
			previusTime = currentTime;
					
			/*Se deltaU = 1, logo a diferença de tempo entre o último update
			 e o tempo atual é de timePerUpdate */
			if(deltaU >= 1) {
				update();
				deltaU = 0;
				updates++;
			}
			
			if(deltaF >= 1) {
				gamePanel.repaint();
				deltaF = 0;
				frames++;
			}
			
			if(System.currentTimeMillis() - lastCheck >= 1000) {
				lastCheck = System.currentTimeMillis();
				
				System.out.println("FPS: " + frames + " | UPS: " +  updates);
				frames = 0;
				updates = 0;
			}
			
			/*Verifica o tempo do ultimo frame.
			 Caso o tempo entre o ultimo frame e agora for
			 maior que o timePerFrame (tempo por frame definido
			 anteriormente) então é necessário imprimir na
			 tela novos frames.*/
			
			/*if(now - lastFrame >= timePerFrame) {
				gamePanel.repaint();
				lastFrame = now;
			}*/
			
		}
		
	}
	
	public Player getPlayer() {
		return player;
	}

	public void WindowFocusLost() {
		player.disableDirBooleans();
		
	}
}
