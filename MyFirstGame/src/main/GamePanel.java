package main;

import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;

import entities.Player;
import inputs.KeyBoardInputs;
import inputs.MouseInputs;

import static main.Game.HEIGHT_GAME_DIMENSION;
import static main.Game.WIDTH_GAME_DIMENSION;



/*Class responsible for draw and administration game elements in window*/
public class GamePanel extends JPanel {
	
	private KeyBoardInputs keyInputs;
	private MouseInputs mouseInputs;
	private Game game;
	

	public GamePanel(Game game) {
		this.game = game;
		keyInputs = new KeyBoardInputs(this);
		mouseInputs = new MouseInputs(this);
		setPanelSize();
		addKeyListener(keyInputs);
		addMouseListener(mouseInputs);
		addMouseMotionListener(mouseInputs);
		
	}
	
	
	private void setPanelSize() {
		Dimension size = new Dimension(WIDTH_GAME_DIMENSION,HEIGHT_GAME_DIMENSION);
		setMinimumSize(size);
		setPreferredSize(size);
		setMaximumSize(size);
		
	}
	


	/*Método reponsável por desenhar elementos graphicos na janela*/
		/*Graphics é uma classe abstrata, Logo g é um objeto que
		 herda Graphics, sendo g um elemento graphico*/
	
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);	//método da super classe de JPanel, JComponent
		
		game.render(g);
	}
	
	public Game getGame() {
		return game;
	}
}
