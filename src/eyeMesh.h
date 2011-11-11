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
	
	float meshSizeX;
	float meshSizeY;
	
	int meshGridX;
	int meshGridY;
	
	int meshTexW;
	int meshTexH;
	
	
	float meshTexCoord[1000][1000][2];
	float meshVerCoord[1000][1000][2];
	
	float meshMaxW;
	float meshMaxH;
	
	
public:
	eyeMesh();
	void updateMeshTexCoord();
	void updateMeshVerCoord();
	void setMeshGrid(int gridW, int gridH);
	void setMeshSize(float sizeX, float sizeY);
	void setMeshTextureSize(int width, int height);
	void setMeshScale(int scale);
	void draw(GLenum  drawMode);
};