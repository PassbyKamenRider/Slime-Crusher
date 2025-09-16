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

	//gameobject references:
	std::vector<Scene::Transform*> belts;
	Scene::Transform* crusher;

	//slime position
	float slime_up = 8.0f;
	float slime_down = 1.5f;
	float slime_left = -4.5f;
	float slime_right = 5.5f;

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

	//music coming from the tip of the leg (as a demonstration):
	std::shared_ptr< Sound::PlayingSample > bgm_loop;

	//slime spawner
	float spawn_timer = 0.0f;
	float spawn_interval = 2.0f;

	//slime stepper
	int step_index = 0;
	float step_timer = 0.0f;
	float step_interval = 0.5f;
	std::vector<float> step_pattern = {
		0.5f, 0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f, 0.5f,
		0.25f, 0.25f, 0.5f,
		0.25f, 0.25f, 0.5f,
		0.25f, 0.25f, 0.5f,
		0.25f, 0.25f, 0.5f
	};

	int crush_count = 0;
	
	//camera:
	Scene::Camera *camera = nullptr;
};
