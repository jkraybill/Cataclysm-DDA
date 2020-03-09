#pragma once
#ifndef PICKUP_H
#define PICKUP_H

#include <vector>

class item;
class item_location;
class Character;
class map;
struct tripoint;

namespace Pickup
{
/**
 * Returns `false` if the player was presented a prompt and decided to cancel the pickup.
 * `true` in other cases.
 */
bool do_pickup( std::vector<item_location> &targets, std::vector<int> &quantities,
                bool autopickup );
/**
 * Returns true if the item is owned by the player, or they consent to stealing.
 * If remember_thief_mode is true, the user's response to thieving is cached
 * until reset_thief_confirmation is called.
 */
bool confirm_ownership_intent( item &newit, bool remember_thief_mode );

bool query_thief();

/**
 * If confirm_ownership_intent was called with remember_thief_mode true, this
 * must be called at the end of a turn / action to remember/forget thief preference.
 */
void reset_thief_confirmation();

enum from_where : int {
    from_cargo = 0,
    from_ground,
    prompt
};

/** Pick up items; 'g' or ',' or via examine() */
void pick_up( const tripoint &p, int min, from_where get_items_from = prompt );
/** Determines the cost of moving an item by a character. */
int cost_to_move_item( const Character &who, const item &it );

/**
 * If character is handling a potentially spillable bucket, gracefully handle what
 * to do with the contents.
 *
 * Returns true if we handled the container, false if we chose to spill the
 * contents and the container still needs to be put somewhere.
 * @param c Character handling the spillable item
 * @param it item to handle
 * @param m map they are on
 */
bool handle_spillable_contents( Character &c, item &it, map &m );
} // namespace Pickup

#endif
