#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "mathFunc.h"
#include "particle.h" 
#include "emmitter.h"

using namespace std;
using namespace glm;

const int MaxParticles = 100000;
float gravity = 9.8;

// calculates random particle initial direction 
vec3 particle_direction() {
	// range [-0.2, 0.2]
	float x = -0.2 + 0.4 * myRandom();
	float y = 2 + 1 * myRandom();
	float z = -0.2 + 0.4 * myRandom();

	vec3 dir = vec3(x, y, z);

	return dir;
}

// returns random particle speed 
float particle_speed() {
	// range betweek [0, 1]
	return myRandom();
}

void newParticle(ParticleBuffer &pb) {
	vec3 origin = vec3(0.0, 0.0, 0.0);
	vec4 water_colour = vec4(0.0, 0.0, 1.0, 0.8);
	Particle p = { origin, water_colour, particle_direction(), particle_speed(), 0.2 };
	pb.push_back(p);
	cout << pb.size();
}


// How particle effected by gravity 
vec3 gravity_motion(Particle &p) {
	p.direction.y -= gravity * 0.004;

	return p.direction;
}

void update_particles(ParticleBuffer &pb) {
	for (int i = 0; i < pb.size(); i++) {
		// recalculate direction due to gravity 
		pb[i].direction = gravity_motion(pb[i]);
		// recalculate position due to gravity 
		pb[i].position = update_vec(pb[i].position, pb[i].direction);
	}
}