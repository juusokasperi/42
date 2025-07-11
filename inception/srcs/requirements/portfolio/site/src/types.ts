import { Dispatch } from 'react';
import { Project } from './data/projects'

export type FilterState = {
	filter: string;
	filteredProjects: Project[];
};

export type FilterAction = {
	type: 'SET_FILTER';
	payload: string;
};

export type DropDownProps = {
	dispatch: Dispatch<FilterAction>;
};
