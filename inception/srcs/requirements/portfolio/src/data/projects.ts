export type Language = 'C' | 'CPP' | 'REACT' | 'TS';

export interface Project {
	id: number;
	title: string;
	description?: string;
	languages: Language[];
	technologies?: string[];
	githubUrl?: string;
	liveUrl?: string;
	image?: string;
};

export const projects: Project[] = [
	{
		id: 6,
		title: "IRC Server",
		description: "An IRC server implementation compliant with IRC clients, featuring a basic bot.",
		languages: ["CPP"],
		image: "imgs/ircserv.png",
		githubUrl: "https://github.com/juusokasperi/42/tree/main/ft_irc"
	},
	{
		id: 5,
		title: "Ray Tracer",
		description: "A compact ray tracing engine built in C, supporting multithreading and bounding volume hierarchy (BVH) acceleration.",
		languages: ["C"],
		technologies: ["Multithreading", "Bounding Volume Hierarchy", "MLX42 Graphics Library"],
		image: "imgs/miniRT.png",
		githubUrl: "https://github.com/juusokasperi/42/tree/main/miniRT"
	},
	{
		id: 4,
		title: "Shell",
		description: "A lightweight BASH-like shell written in C, supporting common shell features and command parsing.",
		languages: ["C"],
		image: "imgs/minishell.png",
		githubUrl: "https://github.com/juusokasperi/42/tree/main/minishell"
	},
	{
		id: 3,
		title: "Wireframe model",
		description: "A graphics application that converts elevation maps into interactive 3D wireframe visualizations.",
		languages: ["C"],
		technologies: ["MLX42 Graphics Library"],
		image: "imgs/fdf.png",
		githubUrl: "https://github.com/juusokasperi/42/tree/main/FdF"
	},
	{
		id: 2,
		title: "Jazz in Helsinki -calendar application",
		description:
			"A full-stack web application for browsing jazz events \
			in the Helsinki area. Built with a React frontend and a \
			RESTful Express/Node.js backend with a PostgreSQL database.",
		languages: ["REACT", "TS"],
		technologies: ["Vite", "Styled Components", "Express/Node.js", "PostGresQL"],
		image: "imgs/jazzcalendar.gif",
		githubUrl: "https://github.com/juusokasperi/fs-gigcalendar-app",
	},
	{
		id: 1,
		title: "Portfolio Website",
		description: "The site you're currently viewing – built with React and styled using Styled Components.",
		languages: ["REACT", "TS"],
		technologies: ["Vite", "Styled Components"],
	},
]

export const LANGUAGE_OPTIONS = [
	{ value: 'ALL', label: 'All languages' },
	{ value: 'C', label: 'C' },
	{ value: 'CPP', label: 'C++' },
	{ value: 'REACT', label: 'React' },
	{ value: 'TS', label: 'TypeScript' }
] as const;
