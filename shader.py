""""
Shader Class

Given a ray with coordinates, the constructors computes the color for the pixel by applying a shading model
Jacob Yoon
251049748
"""

class shader:
    def __init__(self, intersection, direction, camera, objectlist, light):
        """
        Computes the shaded color for the pixel with the args intersection, direction
        camera, objectlist and light.
        """
        #Implementing all the required parameters
        self.__k =intersection[0]
        self.__object =objectlist[objectlist.index(self.__k)]
        t0 =intersection[1]
        self.__inverseMatrix =self.__object.getT().inverse()
        self.__Td =self.__inverseMatrix *direction
        self.__Te =self.__inverseMatrix *camera.getE()
        self.__Ts =self.__inverseMatrix *light.getPosition()
        self.__I =self.__Te +self.__Td.scalarMultiply(t0)
        self.__S =(self.__Ts -self.__I).normalize()
        self.__N =self.__object.normalVector(self.__I)
        self.__R =self.__N.scalarMultiply(2 *(self.__S.removeRow(3).transpose() *self.__N.removeRow(3)).get(0, 0)) -self.__S
        self.__V =(self.__Te -self.__I).normalize()
        self.__Id =max(((self.__N.removeRow(3).transpose() *self.__S.removeRow(3)).get(0, 0)), 0)
        self.__Is =max(((self.__R.removeRow(3).transpose() *self.__V.removeRow(3)).get(0, 0)), 0)
        self.__ref =self.__object.getReflectance()
        self.__col =self.__object.getColor()
        self.__light =light.getIntensity()
        self.__f =0.0
        self.__color =(0, 0, 0)
        
        #This is for when the intersection point is not shadowed by other objects
        if self.__shadowed (self.__object, self.__I, self.__S, objectlist):
            self.__f =self.__ref[0]
            
        else:
            self.__f =self.__ref[0] +self.__ref[1] *self.__Id +self.__ref[2] *(self.__Is **self.__ref[3])
            
        self.__color =(int(self.__f *self.__col[0] *self.__light[0]), int(self.__f *self.__col[1] *self.__light[1]), int(self.__f *self.__col[2] *self.__light[2]))
        
    def __shadowed(self, object, I, S, objectlist):
        """
        This method return true or false depending on the intersection point to the light source
        if it intersects with an object from the scene which will return true.
        """
        matrix = object.getT()
        I = matrix *(I + S.scalarMultiply(0.001))
        S = matrix * S
        #This is for objects and changing the intersection point into coordinates
        for k in objectlist:
            inverseMatrix =k.getTinv()
            Inew =inverseMatrix *I
            Snew =(inverseMatrix *S).normalize()
            
            if k.intersection(Inew, Snew) != -1.0:
                return True
            
        return False
        
    def getShade(self):
        return self.__color