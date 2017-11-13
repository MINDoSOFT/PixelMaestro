/*
	Show.cpp - Library for scheduling PixelMaestro Events.
*/

#include "show.h"

namespace PixelMaestro {

	/**
	 * Constructor. Specifies an initial set of Events to run.
	 * @param controller The controller that will run the Events.
	 * @param events Array of Events to queue.
	 * @param num_events The number of Events in the queue.
	 */
	Show::Show(CueController* controller, Event* events, uint16_t num_events) {
		cue_controller_ = controller;
		set_events(events, num_events);
	}

	/**
	 * Returns the current Event set.
	 * @return Events.
	 */
	Event* Show::get_events() {
		return events_;
	}

	/**
		Returns whether the Show loops back over its Events, or if it just ends.

		@return Whether or not the Show loops.
	*/
	bool Show::get_looping() {
		return loop_;
	}

	/**
	 * Returns the timing method used to run the Show.
	 * @return Timing method.
	 */
	Show::TimingMode Show::get_timing() {
		return timing_;
	}

	/**
		Sets the Events in the Show.

		@param events Array of Events to queue.
		@param num_events The number of Events in the queue.
		@param preserve_current_index If true, continue from the same Event index. Otherwise, start over.
	*/
	void Show::set_events(Event* events, uint16_t num_events, bool preserve_current_index) {
		if (!preserve_current_index) {
			current_index_ = 0;
		}
		events_ = events;
		num_events_ = num_events;
	}

	/**
		Sets whether to loop when the Events are done running.

		@param loop If true, events will loop over from the beginning.
	*/
	void Show::set_looping(bool loop) {
		loop_ = loop;
	}

	/**
		Sets the timing mode.

		@param timing Timing mode used.
	*/
	void Show::set_timing(TimingMode timing) {
		timing_ = timing;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Show::update(const uint32_t& current_time) {		
		// Only run if we're looping, or if we haven't reached the end of the Event list yet.
		if (loop_ || (!loop_ && current_index_ != num_events_)) {
			check_next_event(current_time);
		}
	}

	// Private methods

	/**
	 * Checks the next Event's start time, then runs it if it's ready.
	 */
	void Show::check_next_event(const uint32_t& current_time) {
		/*
			Based on the timing method used, determine whether to run the Event.
			If Absolute, compare the current time to the next Event's start time.
			If Relative, compare the time since the last Event to the next Event's start time.
			After running the Event, update the last run time and current Event index.
		*/
		uint32_t event_time = events_[current_index_].get_time();
		if ((timing_ == TimingMode::Absolute && (current_time >= event_time)) ||
			(timing_ == TimingMode::Relative && ((current_time - last_time_) >= event_time))) {
			cue_controller_->run(events_[current_index_].get_cue());
			last_time_ = current_time;
			update_event_index();

			// Check the next event
			if (current_index_ < num_events_) {
				check_next_event(current_time);
			}
		}
	}

	/**
		Updates the Event index.
	*/
	void Show::update_event_index() {
		// If we've exceeded the number of events, start over from 0
		if (loop_ && (current_index_ + 1 >= num_events_)) {
			current_index_ = 0;
		}
		else {
			current_index_++;
		}
	}
}
