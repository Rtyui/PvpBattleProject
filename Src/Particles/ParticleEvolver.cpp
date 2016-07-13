#include "ParticleEvolver.h"
#include "Helpers.h"

ParticleEvolver::ParticleEvolver()
{
}

ParticleEvolver::~ParticleEvolver()
{
}

void ParticleEvolver::EvolveParticle(Particle* p)
{
	float perc = p->GetLifePercentage();

	uint red = 0, green = 0, blue = 0, alpha = 0;
	Vector2f scale = Vector2f(0.1f, 0.1f);

	for (uint i = 0; i < m_redEvolution.size() - 1; ++i)
	{
		if (m_redEvolution[i].first <= perc && perc <= m_redEvolution[i + 1].first)
		{
			red = m_redEvolution[i].second + (uint)((perc - m_redEvolution[i].first) / (m_redEvolution[i + 1].first - m_redEvolution[i].first) * ((int)m_redEvolution[i + 1].second - (int)m_redEvolution[i].second));
			break;
		}
	}

	for (uint i = 0; i < m_greenEvolution.size() - 1; ++i)
	{
		if (m_greenEvolution[i].first <= perc && perc <= m_greenEvolution[i + 1].first)
		{
			green = m_greenEvolution[i].second + (uint)((perc - m_greenEvolution[i].first) / (m_greenEvolution[i + 1].first - m_greenEvolution[i].first) * ((int)m_greenEvolution[i + 1].second - (int)m_greenEvolution[i].second));
			break;
		}
	}

	for (uint i = 0; i < m_blueEvolution.size() - 1; ++i)
	{
		if (m_blueEvolution[i].first <= perc && perc <= m_blueEvolution[i + 1].first)
		{
			blue = m_blueEvolution[i].second + (uint)((perc - m_blueEvolution[i].first) / (m_blueEvolution[i + 1].first - m_blueEvolution[i].first) * ((int)m_blueEvolution[i + 1].second - (int)m_blueEvolution[i].second));
			break;
		}
	}

	for (uint i = 0; i < m_alphaEvolution.size() - 1; ++i)
	{
		if (m_alphaEvolution[i].first <= perc && perc <= m_alphaEvolution[i + 1].first)
		{
			alpha = m_alphaEvolution[i].second + (uint)((perc - m_alphaEvolution[i].first) / (m_alphaEvolution[i + 1].first - m_alphaEvolution[i].first) * ((int)m_alphaEvolution[i + 1].second - (int)m_alphaEvolution[i].second));
			break;
		}
	}

	for (uint i = 0; i < m_scaleEvolutionX.size() - 1; ++i)
	{
		if (m_scaleEvolutionX[i].first <= perc && perc <= m_scaleEvolutionX[i + 1].first)
		{
			scale.x = m_scaleEvolutionX[i].second + (perc - m_scaleEvolutionX[i].first) / (m_scaleEvolutionX[i + 1].first - m_scaleEvolutionX[i].first) * (m_scaleEvolutionX[i + 1].second - m_scaleEvolutionX[i].second);
			break;
		}
	}

	for (uint i = 0; i < m_scaleEvolutionY.size() - 1; ++i)
	{
		if (m_scaleEvolutionY[i].first <= perc && perc <= m_scaleEvolutionY[i + 1].first)
		{
			scale.y = m_scaleEvolutionY[i].second + (perc - m_scaleEvolutionY[i].first) / (m_scaleEvolutionY[i + 1].first - m_scaleEvolutionY[i].first) * (m_scaleEvolutionY[i + 1].second - m_scaleEvolutionY[i].second);
			break;
		}
	}

	p->SetColor(red, green, blue, alpha);
	p->SetScale(scale);
}

void ParticleEvolver::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		AddEvolutionStage(a);
	}
}

void ParticleEvolver::AddEvolutionStage(const TiXmlAttribute* attribute)
{
	auto v = ParseVector2f(attribute->Value());
	if (StringStartsWith("evol_red", attribute->Name()))
	{
		m_redEvolution.push_back(std::make_pair(v.x, (uint)v.y));
	}
	else if (StringStartsWith("evol_green", attribute->Name()))
	{
		m_greenEvolution.push_back(std::make_pair(v.x, (uint)v.y));
	}
	else if (StringStartsWith("evol_blue", attribute->Name()))
	{
		m_blueEvolution.push_back(std::make_pair(v.x, (uint)v.y));
	}
	else if (StringStartsWith("evol_alpha", attribute->Name()))
	{
		m_alphaEvolution.push_back(std::make_pair(v.x, (uint)v.y));
	}
	else if (StringStartsWith("evol_scaleX", attribute->Name()))
	{
		m_scaleEvolutionX.push_back(std::make_pair(v.x, v.y));
	}
	else if (StringStartsWith("evol_scaleY", attribute->Name()))
	{
		m_scaleEvolutionY.push_back(std::make_pair(v.x, v.y));
	}
}