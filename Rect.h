#pragma once
#include "Vector.h"

template<typename T, int dim>
struct Rect{
	Vec<T, dim> min;
	Vec<T, dim> max;

	Rect(){}
	Rect(Vec<T, dim> min, Vec<T, dim> max){
		this->min = min;
		this->max = max;
	}

	static Rect<T, dim> fromsize(Vec<T, dim> pos, Vec<T, dim> size){
		return Rect(pos, *pos.c().add(&size));
	}

	Vec<T, dim> size(){
		return min.to(&max);
	}

	Vec<T, dim> getPoint(Vec<T, dim>* pos){
		return *min.c().add(size().mul(pos));
	}

	Vec<T, dim> getPointCenter(Vec<T, dim>* pos){
		Vec halfsize = *size().scale(0.5f);
		Vec center = *min.c().add(&halfsize);
		return *center.add(halfsize.mul(pos));
	}

	void loop2d(std::function<void(V2i*, V2i*)> cb){
		V2i abs;
		size().loop2d([&](V2i* rel) {
			abs = min;
			abs.add(rel);
			cb(&abs, rel);
		});
	}

	void collideBox(){
	
	}

	void collidePoint(){
	
	}
};

typedef Rect<float, 2> Rectf;
typedef Rect<int, 2> Recti;