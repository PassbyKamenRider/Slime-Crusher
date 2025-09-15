#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
	// Scene::Transform *hip = nullptr;
	// Scene::Transform *upper_leg = nullptr;
	// Scene::Transform *lower_leg = nullptr;
	// glm::quat hip_base_rotation;
	// glm::quat upper_leg_base_rotation;
	// glm::quat lower_leg_base_rotation;
	// float wobble = 0.0f;

	//gameobject references:
	std::vector<Scene::Transform*> belts;
	Scene::Transform* crusher;

	//slime position
	float slime_up = 8.0f;
	float slime_down = 1.5f;
	float slime_left = -4.5f;
	float slime_right = 5.5f;
	float slime_hit_left = 2.5f;
	float slime_hit_right = 5.0f;

	//slime prefabs
	struct Slime {
		Scene::Transform* transform = nullptr;
		bool isActive = false;
		bool isFalling = false;
		float fall_timer = 0.0f;
		float fall_duration = 0.3f;
		float move_step = 2.0f;
	};
	std::vector<Slime> slimes;

	//belt animation
	float belt_timer = 0.0f;
	float belt_duration = 0.5f;
	std::vector<glm::vec3> belt_positions;
	std::vector<glm::vec3> belt_start_positions;
	size_t belt_offset = 0;

	//crusher animation
	bool isCrushing = false;
	bool isInHitWindow = false;
	float crusher_timer = 0.0f;
	float crusher_duration = 1.0f;
	float crusher_up = 6.0f;
	float crusher_down = 2.0f;

	void BeltRotation(float elapsed);
	void UpdateCrusher(float elapsed);
	void SpawnSlime();
	void SlimeGravity(float elapsed);
	void SlimeStep();

	//glm::vec3 get_leg_tip_position();

	//music coming from the tip of the leg (as a demonstration):
	// std::shared_ptr< Sound::PlayingSample > leg_tip_loop;

	//car honk sound:
	//std::shared_ptr< Sound::PlayingSample > honk_oneshot;
	
	//camera:
	Scene::Camera *camera = nullptr;
};
