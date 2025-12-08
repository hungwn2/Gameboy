/*
 * mapManager.h
 *
 *  Created on: Nov 12, 2025
 *      Author: henryhungwy
 */

#ifndef INC_MAPMANAGER_H_
#define INC_MAPMANAGER_H_


class MapManager
{
	//2 blocks in mario
	std::vector<object>brick_particles;
	std::vector<object>coin_block;
	sf::Image map_sketch;
	sf::Sprite cell_sprite;
	Animation coin_animation;
	Animation question_block_animation;
	Map map;
};


public:
	MapManager();
	unsigned short get_map_sketch_height() const;
	unsigned short get_map_sketch_width const;
	unsigned short get_map_width() const;
	//height fixed
	void add_brick_particles(const unsigned short i_x, const uni)

#endif /* INC_MAPMANAGER_H_ */
