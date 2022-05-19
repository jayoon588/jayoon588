"""tessel class
251049748
Jacob Yoon
CS3388 Assignment 3
"""

import numpy as np
from matrix import matrix

class tessel:   #this will initialize a lighting model using objects, camera, and a light source
    def __init__(self, objectlist, camera, light):
        EPSILON =0.001
        self.__facelist = []    #a list of faces that have normals
        facepoints = [] #a list of points for a face
        lightV =camera.worldToViewingCoordinates(light.getPosition) #this transforms light into coordinates
        lightI =light.getIntensity()    #this simply gets the light intensity
        
        for object in objectlist:
            color =object.getColor()    #to obtain  object color
            u =object.getURange()[0]
            
            while u +object.getUVDelta()[0] <object.getURange()[1] +EPSILON:
                v =object.getVRange()[0]
                
                while v +object.getUVDelta()[1] <object.getVRange()[1] +EPSILON:    #this collects surface points that are trasnformed into coordinates
                    facepoints.append(camera.worldToViewingCoordinates(object.getT() *object.getPoint(u, v)))
                    facepoints.append(camera.worldToViewingCoordinates(object.getT() *object.getPoint(u, v +object.getUVDelta()[1])))
                    facepoints.append(camera.worldToViewingCoordinates(object.getT() *object.getPoint(u +object.getUVDelta()[0], v +object.getUVDelta()[1])))
                    facepoints.append(camera.worldToViewingCoordinates(object.getT() *object.getPoint(u +object.getUVDelta()[0, v])))
                    
                    if not self.__minCoordinate(facepoints, 2) >-camera.getNp():
                        cent =self.centroid(facepoints)
                        norm =self.vectorNormal(facepoints)
                        
                        if not self.__backface(cent, norm): #this will compute the face shading
                            source =self.__vectorToLightSource(lightV, cent)    #this is a vector from the centroid to the light source
                            reflect =self.__vectorSpecular(source, norm)    #this is a reflection vector
                            vector =self.__vectorToEye(cent)    #this is a vector from origin to the surface centroid
                            index =self.__colorIndex(object, norm, source, reflect, vector)
                            facecolor =(int(color[0] *lightI[0] *index), int(color[1] *lightI[1] *index), int(color[2] *lightI[2] *index))
                            pixelFacepoints =[]
                            
                            for point in facepoints:    #for each face point it transforms a point into a 2D pixel coordinates.
                                pixelFacepoints.append(camera.viewingToPixelCoordinates(point))
                            self.__facelist.append((camera.viewingToPixelCoordinates(cent).get(2, 0), pixelFacepoints, facecolor))
                    
                    facepoints =[]  #this reinitializes the list of facepoints
                    v +=object.getUVDelta()[1]
                u +=object.getUVDelta()[0]
                
    def __minCoordinate(self, facepoints, cd):
        minimum =facepoints[0].get(cd, 0)
        
        for point in facepoints:
            if point.get(cd, 0) <minimum:
                minimum =point.get(cd, 0)
        return minimum
    
    def __backface(self, cent, norm):
        return cent.dotProduct(norm) >0.0
    
    def __centroid(self, facepoints):
        sum =matrix(np.zeros((4, 1)))
        
        for point in facepoints:
            sum +=point
        return sum.scalarMultiply(1.0 /float(len(facepoints)))
    
    def __vectorNormal(self, facepoints):
        U =(facepoints[3] -facepoints[1]).removeRow(3).normalize()
        V =(facepoints[2] -facepoints[0]).removeRow(3).normalize()
        return U.crossProduct(V).normalize().insertRow(3, 0.0)
    
    def __vectorToLightSource(self, light, cent):
        return (light.removeRow(3) -cent.removeRow(3)).normalize().insertRow(3, 0.0)
    
    def __vectorSpecular(self, source, norm):
        return source.scalarMultipy(-1.0) +norm.scalarMultiply(2.0 *(source.dotProduct(norm)))
    
    def __vectorToEye(self, cent):
        return cent.removeRow(3).scalarMultiply(-1.0).normalize().insertRow(3, 0.0)
    
    def __colorIndex(self, object, norm, source, reflect, V):
        id =(norm.transpose() *source).get(0, 0)
        inten =(reflect.transpose() *V).get(0, 0)
        if id <0.0:
            id =0.0
        if inten <0.0:
            inten =0.0
        
        ref =object.getReflectance()
        index =ref[0] +ref[1] *id +ref[2] *inten**ref[3]
        return index
    
    def getFaceList(self):
        return self.__facelist
    