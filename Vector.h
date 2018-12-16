#pragma once
#include <vector>
#include <functional>

template<typename T, int dim>
union Vec{
	T vals[dim];
	struct { T x, y, z; };
	struct { T r, g, b; };
	
	
	Vec(){
	
	}

	Vec(T x, T y){
		vals[0] = x;
		vals[1] = y;
	}

	Vec(T x, T y, T z) {
		vals[0] = x;
		vals[1] = y;
		vals[2] = z;
	}

	Vec(const Vec &src){
		memcpy(vals, src.vals, sizeof Vec);
	}

	~Vec(){}

	Vec<T, dim> c(){
		return *this;
	}

	Vec<T, dim>* overwrite(Vec* other) {
		*this = *other;
		return this;
	}

	Vec<T, dim>* add(Vec<T, dim>* other){
		return map([&](T* val, int i) {
			*val += other->vals[i];
		});
	}

	Vec<T, dim>* sub(Vec<T, dim>* other){
		return map([&](T* val, int i) {
			*val -= other->vals[i];
		});
	}

	Vec<T, dim>* mul(Vec<T, dim>* other) {
		return map([&](T* val, int i) {
			*val *= other->vals[i];
		});
	}

	Vec<T, dim>* div(Vec<T, dim>* other){
		return map([&](T* val, int i) {
			*val /= other->vals[i];
		});
	}

	Vec<T, dim>* scale(float scalar){
		return map([&](T* val, int i) {
			*val *= scalar;
		});
	}

	float length(){
		T sum = 0;
		map([&](T* val, int i) {
			sum += *val * *val;
		});
		return powf(sum, 0.5f);
	}
	
	Vec<T, dim>* normalize(){
		return scale(1 / length());
	}
	
	Vec<T, dim> to(Vec<T, dim>* other){
		return *other->c().sub(this);
	}

	Vec<T, dim> lerp(Vec<T, dim>* other, float r){
		return *this->c().add(other->scale(r));
	}

	float dot(Vec<T, dim>* other){
		float sum = 0;
		map([&](float* val, int i) {
			sum += *val * other->vals[i];
		});
		return powf(sum, 0.5f);
	}

	Vec<T, dim>* map(std::function<void(T*,int)> cb){
		for (int i = 0; i < dim; i++)
		{
			cb(&vals[i], i);
		}
		return this;
	}

	void loop2d(std::function<void(Vec<int, 2>*)> cb){
		Vec<int, 2> temp;
		for(temp.x = 0;temp.x < x; temp.x++){
			for (temp.y = 0; temp.y < y; temp.y++) {
				cb(&temp);
			}
		}
	}
};

typedef Vec<float,2> V2f;
typedef Vec<int,2> V2i;
typedef Vec<int, 3> V3i;