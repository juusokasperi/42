import { Project } from '../../data/projects'
import { ProjectImg, ProjectDiv, Title, Element, Link } from './styled'

interface ProjectCardProps {
	project: Project;
}

const ProjectCard: React.FC<ProjectCardProps> = ({ project }) => {
	return (
		<ProjectDiv>
			<Title>
				{project.title}
			</Title>
			{project.image &&
					<ProjectImg src={`${import.meta.env.BASE_URL}/${project.image}`} alt={project.title} />}
			{project.description &&
					<Element padBottom="0.75em">{project.description}</Element>}
			<Element>
				<b>Languages:</b> {project.languages.join(', ')}
			</Element>
			{project.technologies && (
				<Element>
				<b>Technologies: </b>
				{project.technologies.join(', ')}
				</Element>
			)}
			{(project.githubUrl || project.liveUrl) && (
				<Element padTop="0.5em" padBottom="0.5em">
					{project.githubUrl &&
		 			<Link href={project.githubUrl} target="_blank">
						GitHub
					</Link>
					}
				{project.githubUrl && project.liveUrl && <>{" | "}</>}
				{project.liveUrl &&
					<>
					Deployed{" "}
					<Link href={project.liveUrl} target="_blank">
						here
					</Link></>}
					</Element>
				)}
		</ProjectDiv>
	);
};

export default ProjectCard;

