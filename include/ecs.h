#pragma once
#include <iostream>

class Test {
	public:
		void foo();
};

class Transform {
	public:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
} ;

class Entity {
	private:
		Transform localTransform;
		boolean localIsDirty;
		Transform globalTransform;
		boolean globalIsDirty;
	public:
		
	//public:
		
};

class Component {
	//private:
	//public:
};



















































class Transform {
    //Vector3 position;
    //Vector3 rotation;
    //Vector3 scale;
};

enum ReferenceFrame {
	RF_GLOBAL, RF_LOCAL 
};

class Entity {
    private:
        const int id;
		
        Transform globalTransform;
        Transform localTransform;
		unsigned short hierarchyDepth;
		
		bool globalTransformIsOutdated;
		

    public:
		Transform* transform(ReferenceFrame frame);
        void setTransform(Transform* t, ReferenceFrame frame);
		int Id() { return id; }
};

class Component {
	private:
		int id;
		
	public:
		int Id() { return id; }
};