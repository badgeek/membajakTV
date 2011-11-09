/*
 *  eyeMesh.h
 *  membajakTV
 *
 *  Created by Budi Prakosa on 11/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class eyeMesh {
private:
	
	int meshScale;
	int meshSizeX;
	int meshSizeY;
	
	int meshGridX;
	int meshGridY;
	
	int meshTexW;
	int meshTexH;
	
	
	float meshTexCoord[1000][1000][2];
	
public:
	eyeMesh();
	void updateMeshTexCoord();
	void setMeshGrid(int gridW, int gridH);
	void setMeshSize(int sizeX, int sizeY);
	void setMeshTextureSize(int width, int height);
	void setMeshScale(int scale);
	void draw(GLenum  drawMode);
};