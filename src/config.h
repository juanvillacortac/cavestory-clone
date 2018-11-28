#ifndef CONFIG_H_
#define CONFIG_H_

namespace config {
	enum GraphicsQuality {
		HIGH,
		ORIGINAL
	};

	enum ScaleType {
		INT,
		FLOAT
	};

	GraphicsQuality getGraphicsQuality();

	ScaleType getScaleType();

	bool getFullscreen();
}

#endif // CONFIG_H_
