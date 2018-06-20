#include "glut.h"

enum material {
	brass, bronze, polishedbronze, chrome, copper, polishedcopper, gold, pollishedgold, tin, silver, polishedsilver,
	emerald, jade, obsidian, perl, ruby, turquoise, blackplastic, cyanplastic, greenplastic, redplastic, whiteplastic,
	yellowplastic, blackrubber, cyanrubber, greenrubber, redrubber, whiterubber, yellowrubber
};
#pragma endregion


//Hàm set material
#pragma region Material
void applyMaterial(float ambient[], float diffuse[], float specular[], float shiness) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void setMaterial(material myMaterial) {
	switch (myMaterial) {
	case brass: {
		float mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
		float mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
		float mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
		float shine = 1.8974f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case bronze: {
		float mat_ambient[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
		float mat_diffuse[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
		float mat_specular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
		float shine = 1.6f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedbronze: {
		float mat_ambient[] = { 0.25f, 0.148f, 0.06475f, 1.0f };
		float mat_diffuse[] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
		float mat_specular[] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case chrome: {
		float mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		float mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
		float shine = 0.1f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case copper: {
		float mat_ambient[] = { 0.19125f, 0.0735f, 0.0225f, 1.0f };
		float mat_diffuse[] = { 0.7038f, 0.27048f, 0.0828f, 1.0f };
		float mat_specular[] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedcopper: {
		float mat_ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
		float mat_diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
		float mat_specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
		float shine = 1.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case gold: {
		float mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
		float mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
		float mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
		float shine = 1.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case pollishedgold: {
		float mat_ambient[] = { 0.24725f, 0.2245f, 0.0645f, 1.0f };
		float mat_diffuse[] = { 0.34615f, 0.3143f, 0.0903f, 1.0f };
		float mat_specular[] = { 0.797357f, 0.723991f, 0.208006f, 1.0f };
		float shine = 1.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case tin: {
		float mat_ambient[] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
		float mat_diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
		float mat_specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
		float shine = 1.84615f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case silver: {
		float mat_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
		float mat_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
		float mat_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
		float shine = 1.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedsilver: {
		float mat_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
		float mat_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
		float mat_specular[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
		float shine = 0.1f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case emerald: {
		float mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
		float mat_diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
		float mat_specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case jade: {
		float mat_ambient[] = { 0.135f, 0.2225f, 0.1575f, 0.95f };
		float mat_diffuse[] = { 0.54f, 0.89f, 0.63f, 0.95f };
		float mat_specular[] = { 0.316228f, 0.316228f, 0.316228f, 0.95f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case obsidian: {
		float mat_ambient[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
		float mat_diffuse[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
		float mat_specular[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
		float shine = .1f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case perl: {
		float mat_ambient[] = { 0.25f, 0.20725f, 0.20725f, 0.922f };
		float mat_diffuse[] = { 1.0f, 0.829f, 0.829f, 0.922f };
		float mat_specular[] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
		float shine = 1.264f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case ruby: {
		float mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
		float mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
		float mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case turquoise: {
		float mat_ambient[] = { 0.1f, 0.18725f, 0.1745f, 0.8f };
		float mat_diffuse[] = { 0.396f, 0.74151f, 0.69102f, 0.8f };
		float mat_specular[] = { 0.297254f, 0.30829f, 0.306678f, 0.8f };
		float shine = 0.1f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case blackplastic: {
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case cyanplastic: {
		float mat_ambient[] = { 0.0f,0.1f,0.06f ,1.0f };
		float mat_diffuse[] = { 0.0f,0.50980392f,0.50980392f,1.0f };
		float mat_specular[] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
		float shine = 0.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case greenplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
		float mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case redplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.0f,0.0f,1.0f };
		float mat_specular[] = { 0.7f,0.6f,0.6f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case whiteplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.55f,0.55f,0.55f,1.0f };
		float mat_specular[] = { 0.70f,0.70f,0.70f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case yellowplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.0f,1.0f };
		float mat_specular[] = { 0.60f,0.60f,0.50f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case blackrubber: {
		float mat_ambient[] = { 0.02f, 0.02f, 0.02f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case cyanrubber: {
		float mat_ambient[] = { 0.05f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.4f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.04f,0.04f,1.0f };
		float shine = 0.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case greenrubber: {
		float mat_ambient[] = { 0.0f,0.05f,0.0f,1.0f };
		float mat_diffuse[] = { 0.4f,0.5f,0.4f,1.0f };
		float mat_specular[] = { 0.04f,0.7f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case redrubber: {
		float mat_ambient[] = { 0.05f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.4f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.04f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case whiterubber: {
		float mat_ambient[] = { 0.05f,0.05f,0.05f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
		float mat_specular[] = { 0.7f,0.7f,0.7f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case yellowrubber: {
		float mat_ambient[] = { 0.05f,0.05f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.7f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	default:
		break;
	}
}
#pragma endregion
