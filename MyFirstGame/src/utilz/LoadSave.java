package utilz;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.InputStream;

import javax.imageio.ImageIO;

import static main.Game.TILES_IN_HEIGHT;
import static main.Game.TILES_IN_WIDTH;

public abstract class LoadSave {

	public static BufferedImage getImage (String fileName) {
		BufferedImage img = null;
		InputStream is = LoadSave.class.getResourceAsStream("/" + fileName);

		try {
			
			img = ImageIO.read(is);
			 
		}catch(IOException e){
			e.printStackTrace();
		}finally {
			try{
				is.close();
			}catch(IOException e) {
				e.printStackTrace();	 
			} 
		}
		
		return img;
	}
	
	public static int[][] getLvlData(String fileName){
		int[][] lvlData = new int[TILES_IN_WIDTH][TILES_IN_HEIGHT];
		BufferedImage img = getImage(fileName);
		
		for(int i = 0 ; i < TILES_IN_WIDTH ; i++) {
			
			for(int j = 0 ; j < TILES_IN_HEIGHT ; j++) {
				
				Color color = new Color(img.getRGB(i,j));
				lvlData[i][j] = color.getRed();
				
			}
			
		}
		
		return lvlData;
	}
}
