#pragma once
enum material {
	brass, bronze, polishedbronze, chrome, copper, polishedcopper, gold, pollishedgold, tin, silver, polishedsilver,
	emerald, jade, obsidian, perl, ruby, turquoise, blackplastic, cyanplastic, greenplastic, redplastic, whiteplastic,
	yellowplastic, blackrubber, cyanrubber, greenrubber, redrubber, whiterubber, yellowrubber
};
void applyMaterial(float ambient[], float diffuse[], float specular[], float shiness);
void setMaterial(material myMaterial);
