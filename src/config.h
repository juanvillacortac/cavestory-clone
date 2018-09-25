#ifndef CONFIG_H_
#define CONFIG_H_

namespace config {
	enum GraphicsQuality {
		HIGH,
		ORIGINAL
	};

	GraphicsQuality getGraphicsQuality();
}

#endif // CONFIG_H_
