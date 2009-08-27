#ifndef CHARACTER_TYPE_HPP_INCLUDED
#define CHARACTER_TYPE_HPP_INCLUDED

#include <string>

#include "boost/scoped_ptr.hpp"
#include "boost/shared_ptr.hpp"

#include "current_generator.hpp"
#include "formula_fwd.hpp"
#include "frame.hpp"
#include "thread.hpp"
#include "variant.hpp"
#include "wml_node.hpp"

class character_type;

typedef boost::shared_ptr<character_type> character_type_ptr;
typedef boost::shared_ptr<const character_type> const_character_type_ptr;

namespace wml {
class modifier;
}

class character_type
{
public:
	static void init(wml::const_node_ptr node);
	static const_character_type_ptr get(const std::string& id);
	explicit character_type(wml::const_node_ptr node);

	const_character_type_ptr get_modified(const std::string& id, const wml::modifier& modifier) const;
	bool modification_cached(const std::string& id) const;

	const std::string& id() const { return id_; }
	const frame& get_frame() const { return stand_; }
	const frame& icon_frame() const { return icon_frame_.get() ? *icon_frame_ : get_frame(); }
	const frame& portrait_frame() const { return portrait_frame_.get() ? *portrait_frame_ : get_frame(); }
	const frame& name_frame() const { return name_frame_.get() ? *name_frame_ : get_frame(); }
	const frame* stand_up_slope_frame() const { return stand_up_slope_frame_.get(); }
	const frame* stand_down_slope_frame() const { return stand_down_slope_frame_.get(); }
	const frame* idle_frame() const { return idle_frame_.get(); }
	const frame* turn_frame() const { return turn_frame_.get(); }
	const frame* walk_frame() const { return walk_frame_.get(); }
	const frame* run_frame() const { return run_frame_.get(); }
	const frame* jump_frame() const { return jump_frame_.get(); }
	const frame* fall_frame() const { return fall_frame_.get(); }
	const frame* crouch_frame() const { return crouch_frame_.get(); }
	const frame* roll_frame() const { return roll_frame_.get(); }
	const frame* lookup_frame() const { return lookup_frame_.get(); }
	const frame* gethit_frame() const { return gethit_frame_.get(); }
	const frame* attack_frame() const { return attack_frame_.get(); }
	const frame* jump_attack_frame() const { return jump_attack_frame_.get(); }
	const frame* fall_spin_attack_frame() const { return fall_spin_attack_frame_.get(); }
	const frame* up_attack_frame() const { return up_attack_frame_.get(); }
	const frame* run_attack_frame() const { return run_attack_frame_.get(); }
	const frame* die_frame() const { return die_frame_.get(); }
	const frame* fly_frame() const { return fly_frame_.get(); }
	const frame* slide_frame() const { return slide_frame_.get(); }
	const frame* spring_frame() const { return spring_frame_.get(); }
	const frame* swim_side_idle_frame() const { return swim_side_idle_frame_.get(); }
	const frame* swim_down_idle_frame() const { return swim_down_idle_frame_.get(); }
	const frame* swim_up_idle_frame() const { return swim_up_idle_frame_.get(); }
	const frame* swim_side_frame() const { return swim_side_frame_.get(); }
	const frame* swim_down_frame() const { return swim_down_frame_.get(); }
	const frame* swim_up_frame() const { return swim_up_frame_.get(); }
	const frame* push_frame() const { return push_frame_.get(); }
	const frame* interact_frame() const { return interact_frame_.get(); }

	bool has_swim_frames() const { return swim_side_frame(); }

	int walk() const { return walk_; }
	int jump() const { return jump_; }
	int boost() const { return boost_; }
	int glide() const { return glide_; }
	int climb() const { return climb_; }
	int hitpoints() const { return hitpoints_; }
	int springiness() const { return springiness_; }
	int friction() const { return friction_; }
	int traction() const { return traction_; }
	int weight() const { return weight_; }
	int mass() const { return mass_; }
	int feet_width() const { return feet_width_; }
	bool is_vehicle() const { return is_vehicle_; }
	int passenger_x() const { return passenger_x_; }
	int passenger_y() const { return passenger_y_; }
	const std::string& vehicle_die_object() const { return vehicle_die_object_; }
	const std::string& loop_sound() const { return loop_sound_; }

	game_logic::const_formula_ptr get_event_handler(const std::string& frame_id) const;

	const std::map<std::string, variant>& variables() const { return variables_; }

	current_generator_ptr current_generator() const { return current_generator_; }
	int radial_distortion() const { return radial_distortion_; }
	int radial_distortion_intensity() const { return radial_distortion_intensity_; }
private:
	wml::const_node_ptr wml_;

	std::string id_;
	graphics::texture portrait_;
	frame stand_;
	typedef boost::scoped_ptr<frame> frame_ptr;
	frame_ptr portrait_frame_, name_frame_, icon_frame_,
	          stand_up_slope_frame_, stand_down_slope_frame_, idle_frame_,
	          turn_frame_, walk_frame_, run_frame_, jump_frame_, fall_frame_,
	          crouch_frame_, roll_frame_, lookup_frame_, gethit_frame_,
			  attack_frame_, jump_attack_frame_, fall_spin_attack_frame_,
			  up_attack_frame_, run_attack_frame_,
			  die_frame_, fly_frame_, slide_frame_, spring_frame_,
			  swim_side_idle_frame_,swim_down_idle_frame_,swim_up_idle_frame_,
			  swim_side_frame_,swim_down_frame_,swim_up_frame_,
	          push_frame_, interact_frame_;
	int walk_;
	int jump_;
	int boost_;
	int glide_;
	int climb_;
	int hitpoints_;
	int springiness_;
	int friction_;
	int traction_;
	int weight_;
	int mass_;
	int feet_width_;
	bool is_vehicle_;
	int passenger_x_, passenger_y_;
	std::string vehicle_die_object_;
	std::string loop_sound_;

	//formulas that are executed when a frame with the corresponding ID
	//is started.
	std::map<std::string, game_logic::const_formula_ptr> event_handlers_;

	std::map<std::string, variant> variables_;

	current_generator_ptr current_generator_;

	int radial_distortion_, radial_distortion_intensity_;

	//a cache of character types resulting from acquiring a powerup.
	mutable std::map<std::string, const_character_type_ptr> modified_cache_;
	mutable threading::mutex modified_cache_mutex_;
};

#endif
