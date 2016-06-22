#ifndef BDN_UiLength_H_
#define BDN_UiLength_H_


namespace bdn
{
	
/** Represents a length or distance to use sizing and spacing user interface elements.

	The recommended unit is UiLength::Unit::sem.

	Background information
	----------------------

	Distances and sizes for UI elements are surprisingly difficult to specify in a way that works
	well on all devices and in all situations.

	Pixels are very inadequate for this reason. High resolution monitors often have the same physical
	size as lower resolution monitors, but their pixels are often much smaller. So if you were to specify
	the space between two elements in pixels then the distance might look good on one display, but would
	be much too small or too big on other displays.

	Another consideration are viewing distances. You do not want UI elements to be the same physical size on a phone as they are
	on a monitor. Phones are usually held at a smaller viewing distance than monitors, so UI elements can be physically
	smaller and still be perfectly readable and usable.
	On the other extreme, consider a huge display in a football stadium. The viewing distance for people is much bigger
	than on a normal desktop monitor, so texts and UI elements must also be a lot bigger.
	
	Another point for consideration are user preferences. Visually impaired users might need UI elements to be much bigger
	than users with perfect eyesight. So UI elements should also scale with user preferences.

	So these are the main problems when defining UI lengths:

	- Different pixel densities of displays (high resolution displays vs. low resolution displays)
	- Different viewing distances (phone vs. monitor vs TV vs stadium screen).
	- Different user preferences

	The sem unit  (UiLength::sem)
	-----------------------------
	
	The unit that solves all of the problems described above is called "sem". 1 sem equals the height of the default UI font
	of whatever screen that the UI element is currently on.

	Why does sem solve all the problems described above?

	On a desktop monitor, the operating system and user will choose a system font size that is comfortably readable
	on the monitor in use. Multi-monitor systems with different monitor resolutions will also usually use different
	font sizes for each monitor, so that text on each monitor is readable comfortably.

	If the user has a visual impairment then he or she will adjust the operating system settings to increase the default
	font size.

	On different device types (phones, tablets, TVs and huge stadium screens) the default font size will be adjusted by the operating
	system according to the expected viewing distance of the user. Phone and tablet font sizes are smaller, TV fonts are bigger
	and stadium screen font sizes are huge.

	So the best way to specify distances is clearly in relation to the screen's default font size. So "sem" is the recommended
	unit to use for UI sizes and lengths.

	The term "sem" is derived from the term "em" (commonly used in CSS, for example), which denotes a size relative to a font size.
	The leading "s" is added because the font in question is the default screen font, not any custom font that might be selected for an element.

	Note that 1 sem is actually a rather large size, compared to a pixel. It is the height of the font. So some distances will actually
	be specified as fraction. For example, the space between two elements might be 1.5 sem or something similar.

	The "96 DPI pixel" unit (UiLength::pixel96)
	-------------------------------------------

	Another solution to the problems is to define the unit as the size of a "legacy pixel" from the times when one could reasonably
	assume that a pixel would have a certain size.

	An oversimplified definition for this unit would be "the perceived size a pixel would have on a 96 DPI desktop monitor".
	
	Old displays on the Windows operating system often had a pixel density of 96 DPI (also sometimes referred to as 96 PPI). The
	idea is to use that as a unit, because it allows old pixel-based measurements to be used on newer high resolution system
	without requiring any conversion.

	The term "96 DPI pixel" is actually an incorrect name, because the unit size does not only depend on the pixel
	density of the screen. On most systems that use something like this, it also takes into account other variables,
	like the expected viewing distance of the device and even user preferences. On Windows the size of this unit
	depends only on the UI scaling factor for the screen, which in turn depends on the screen's hardware DPI, the resolution,
	the expected viewing distance and user preferences.

	So this unit is actually similar to the sem unit on most systems (i.e. there is a constant conversion factor between sem and
	"96 DPI pixels").

	Nevertheless, using sem is still preferred, because defining a unit based on the size perceived on some old legacy hardware is not
	a useful definition.	

	The unit constant for the "96 DPI pixel" is UiLength::pixel96.


	The "real pixel" unit (UiLength::realPixel)
	--------------------------------------------

	This unit is simply the size of an actual real screen pixel. It varies greatly between devices and
	screens and should usually be avoided.
	It is only useful when dealing with values for a concrete screen on a concrete system. For example, it could
	be used at runtime to compare sizes of two UI elements if they are on the same screen.

	*/
class UiLength : public Base
{
public:
	enum Unit
	{
		/** 1 sem equals the height of the screen's default UI font.
		
			This is the recommended unit for UI sizing and spacing. It is designed to create UIs
			that scale perfectly under all conditions and produce the optimal result for the
			screen, DPI/PPI setting, viewing distance and preference of the user.

			See the UiLength class documentation for more information.
			*/
		sem,


		/** An actual pixel on the screen. The actual size of such a pixel depends on the screen's pixel
			resolution.
			Using this for specifing the sizes or spacing of UI elements is highly discouraged, as these
			values depend heavily on the device that the UI element is displayed on.
			*/
		realPixel,


		/** This unit corresponds roughly to the perceived size of a pixel on an legacy 96 dpi desktop monitor.
			
			Note that this unit actually takes other factors into account as well (expected viewing distance of the device,
			user preferences, etc.). See the UiLength class documentation for more information.

			The unit is comparable to the UiLength::sem unit on most systems. I.e. there is often a constant conversion factor
			between sem and pixel96.

			However, using sem is still preferred, because defining something on the basis of some old legacy system is
			not a good future proof definition.
			*/
		pixel96
	};


	UiLength()
	{
		unit = sem;
		value = 0;		
	};


	UiLength(Unit unit, double value)
	{
		this->unit = unit;
		this->value = value;
	}


	bool operator==(const UiLength& o) const
	{
		return (unit==o.unit && value==o.value);
	}

	bool operator!=(const UiLength& o) const
	{
		return !operator==(o);
	}

	Unit	unit;	
	double	value;	
};


}


#endif

